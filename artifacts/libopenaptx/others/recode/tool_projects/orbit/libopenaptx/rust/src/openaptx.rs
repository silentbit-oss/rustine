//! Open Source implementation of Audio Processing Technology codec (aptX)
//! Copyright (C) 2018-2021  Pali Rohár <pali.rohar@gmail.com>
//! Rust translation (C) 2026

use std::mem;

// Constants
pub const OPENAPTX_MAJOR: i32 = 0;
pub const OPENAPTX_MINOR: i32 = 2;
pub const OPENAPTX_PATCH: i32 = 1;

// Public version globals
pub static aptx_major: i32 = OPENAPTX_MAJOR;
pub static aptx_minor: i32 = OPENAPTX_MINOR;
pub static aptx_patch: i32 = OPENAPTX_PATCH;

// Constants
const NB_CHANNELS: usize = 2;
const NB_SUBBANDS: usize = 4;
const NB_FILTERS: usize = 2;
const FILTER_TAPS: usize = 16;
const LATENCY_SAMPLES: usize = 90;

// Quantization lookup tables for Low Frequency (LF) band
static quantize_intervals_LF: [i32; 65] = [
      -9948,    9948,   29860,   49808,   69822,   89926,  110144,  130502,
     151026,  171738,  192666,  213832,  235264,  256982,  279014,  301384,
     324118,  347244,  370790,  394782,  419250,  444226,  469742,  495832,
     522536,  549890,  577936,  606720,  636290,  666700,  698006,  730270,
     763562,  797958,  833538,  870398,  908640,  948376,  989740, 1032874,
    1077948, 1125150, 1174700, 1226850, 1281900, 1340196, 1402156, 1468282,
    1539182, 1615610, 1698514, 1789098, 1888944, 2000168, 2125700, 2269750,
    2438670, 2642660, 2899462, 3243240, 3746078, 4535138, 5664098, 7102424,
    8897462,
];
static invert_quantize_dither_factors_LF: [i32; 65] = [
       9948,   9948,   9962,   9988,  10026,  10078,  10142,  10218,
      10306,  10408,  10520,  10646,  10784,  10934,  11098,  11274,
      11462,  11664,  11880,  12112,  12358,  12618,  12898,  13194,
      13510,  13844,  14202,  14582,  14988,  15422,  15884,  16380,
      16912,  17484,  18098,  18762,  19480,  20258,  21106,  22030,
      23044,  24158,  25390,  26760,  28290,  30008,  31954,  34172,
      36728,  39700,  43202,  47382,  52462,  58762,  66770,  77280,
      91642, 112348, 144452, 199326, 303512, 485546, 643414, 794914,
    1000124,
];
static quantize_dither_factors_LF: [i32; 65] = [
        0,     4,     7,    10,    13,    16,    19,    22,
       26,    28,    32,    35,    38,    41,    44,    47,
       51,    54,    58,    62,    65,    70,    74,    79,
       84,    90,    95,   102,   109,   116,   124,   133,
      143,   154,   166,   180,   195,   212,   231,   254,
      279,   308,   343,   383,   430,   487,   555,   639,
      743,   876,  1045,  1270,  1575,  2002,  2628,  3591,
     5177,  8026, 13719, 26047, 45509, 39467, 37875, 51303,
        0,
];
static quantize_factor_select_offset_LF: [i16; 65] = [
      0, -21, -19, -17, -15, -12, -10,  -8,
     -6,  -4,  -1,   1,   3,   6,   8,  10,
     13,  15,  18,  20,  23,  26,  29,  31,
     34,  37,  40,  43,  47,  50,  53,  57,
     60,  64,  68,  72,  76,  80,  85,  89,
     94,  99, 105, 110, 116, 123, 129, 136,
    144, 152, 161, 171, 182, 194, 207, 223,
    241, 263, 291, 328, 382, 467, 522, 522,
    522,
];

// Quantization lookup tables for Medium-Low Frequency (MLF) band
static quantize_intervals_MLF: [i32; 9] = [
    -89806, 89806, 278502, 494338, 759442, 1113112, 1652322, 2720256, 5190186,
];
static invert_quantize_dither_factors_MLF: [i32; 9] = [
    89806, 89806, 98890, 116946, 148158, 205512, 333698, 734236, 1735696,
];
static quantize_dither_factors_MLF: [i32; 9] = [
    0, 2271, 4514, 7803, 14339, 32047, 100135, 250365, 0,
];
static quantize_factor_select_offset_MLF: [i16; 9] = [
    0, -14, 6, 29, 58, 96, 154, 270, 521,
];

// Quantization lookup tables for Medium-High Frequency (MHF) band
static quantize_intervals_MHF: [i32; 3] = [
    -194080, 194080, 890562,
];
static invert_quantize_dither_factors_MHF: [i32; 3] = [
    194080, 194080, 502402,
];
static quantize_dither_factors_MHF: [i32; 3] = [
    0, 77081, 0,
];
static quantize_factor_select_offset_MHF: [i16; 3] = [
    0, -33, 136,
];

// Quantization lookup tables for High Frequency (HF) band
static quantize_intervals_HF: [i32; 5] = [
    -163006, 163006, 542708, 1120554, 2669238,
];
static invert_quantize_dither_factors_HF: [i32; 5] = [
    163006, 163006, 216698, 361148, 1187538,
];
static quantize_dither_factors_HF: [i32; 5] = [
    0, 13423, 36113, 206598, 0,
];
static quantize_factor_select_offset_HF: [i16; 5] = [
    0, -8, 33, 95, 262,
];

// HD Quantization lookup tables for Low Frequency (LF) band
static hd_quantize_intervals_LF: [i32; 257] = [
      -2436,    2436,    7308,   12180,   17054,   21930,   26806,   31686,
      36566,   41450,   46338,   51230,   56124,   61024,   65928,   70836,
      75750,   80670,   85598,   90530,   95470,  100418,  105372,  110336,
     115308,  120288,  125278,  130276,  135286,  140304,  145334,  150374,
     155426,  160490,  165566,  170654,  175756,  180870,  185998,  191138,
     196294,  201466,  206650,  211850,  217068,  222300,  227548,  232814,
     238096,  243396,  248714,  254050,  259406,  264778,  270172,  275584,
     281018,  286470,  291944,  297440,  302956,  308496,  314056,  319640,
     325248,  330878,  336532,  342212,  347916,  353644,  359398,  365178,
     370986,  376820,  382680,  388568,  394486,  400430,  406404,  412408,
     418442,  424506,  430600,  436726,  442884,  449074,  455298,  461554,
     467844,  474168,  480528,  486922,  493354,  499820,  506324,  512866,
     519446,  526064,  532722,  539420,  546160,  552940,  559760,  566624,
     573532,  580482,  587478,  594520,  601606,  608740,  615920,  623148,
     630426,  637754,  645132,  652560,  660042,  667576,  675164,  682808,
     690506,  698262,  706074,  713946,  721876,  729868,  737920,  746036,
     754216,  762460,  770770,  779148,  787594,  796108,  804694,  813354,
     822086,  830892,  839774,  848736,  857776,  866896,  876100,  885386,
     894758,  904218,  913766,  923406,  933138,  942964,  952886,  962908,
     973030,  983254,  993582, 1004020, 1014566, 1025224, 1035996, 1046886,
    1057894, 1069026, 1080284, 1091670, 1103186, 1114838, 1126628, 1138558,
    1150634, 1162858, 1175236, 1187768, 1200462, 1213320, 1226346, 1239548,
    1252928, 1266490, 1280242, 1294188, 1308334, 1322688, 1337252, 1352034,
    1367044, 1382284, 1397766, 1413494, 1429478, 1445728, 1462252, 1479058,
    1496158, 1513562, 1531280, 1549326, 1567710, 1586446, 1605550, 1625034,
    1644914, 1665208, 1685932, 1707108, 1728754, 1750890, 1773542, 1796732,
    1820488, 1844840, 1869816, 1895452, 1921780, 1948842, 1976680, 2005338,
    2034868, 2065322, 2096766, 2129260, 2162880, 2197708, 2233832, 2271352,
    2310384, 2351050, 2393498, 2437886, 2484404, 2533262, 2584710, 2639036,
    2696578, 2757738, 2822998, 2892940, 2968278, 3049896, 3138912, 3236760,
    3345312, 3467068, 3605434, 3765154, 3952904, 4177962, 4452178, 4787134,
    5187290, 5647128, 6159120, 6720518, 7332904, 8000032, 8726664, 9518152,
   10380372,
];
static hd_invert_quantize_dither_factors_LF: [i32; 257] = [
      2436,   2436,   2436,   2436,   2438,   2438,   2438,   2440,
      2442,   2442,   2444,   2446,   2448,   2450,   2454,   2456,
      2458,   2462,   2464,   2468,   2472,   2476,   2480,   2484,
      2488,   2492,   2498,   2502,   2506,   2512,   2518,   2524,
      2528,   2534,   2540,   2548,   2554,   2560,   2568,   2574,
      2582,   2588,   2596,   2604,   2612,   2620,   2628,   2636,
      2646,   2654,   2664,   2672,   2682,   2692,   2702,   2712,
      2722,   2732,   2742,   2752,   2764,   2774,   2786,   2798,
      2810,   2822,   2834,   2846,   2858,   2870,   2884,   2896,
      2910,   2924,   2938,   2952,   2966,   2980,   2994,   3010,
      3024,   3040,   3056,   3070,   3086,   3104,   3120,   3136,
      3154,   3170,   3188,   3206,   3224,   3242,   3262,   3280,
      3300,   3320,   3338,   3360,   3380,   3400,   3422,   3442,
      3464,   3486,   3508,   3532,   3554,   3578,   3602,   3626,
      3652,   3676,   3702,   3728,   3754,   3780,   3808,   3836,
      3864,   3892,   3920,   3950,   3980,   4010,   4042,   4074,
      4106,   4138,   4172,   4206,   4240,   4276,   4312,   4348,
      4384,   4422,   4460,   4500,   4540,   4580,   4622,   4664,
      4708,   4752,   4796,   4842,   4890,   4938,   4986,   5036,
      5086,   5138,   5192,   5246,   5300,   5358,   5416,   5474,
      5534,   5596,   5660,   5726,   5792,   5860,   5930,   6002,
      6074,   6150,   6226,   6306,   6388,   6470,   6556,   6644,
      6736,   6828,   6924,   7022,   7124,   7228,   7336,   7448,
      7562,   7680,   7802,   7928,   8058,   8192,   8332,   8476,
      8624,   8780,   8940,   9106,   9278,   9458,   9644,   9840,
     10042,  10252,  10472,  10702,  10942,  11194,  11458,  11734,
     12024,  12328,  12648,  12986,  13342,  13720,  14118,  14540,
     14990,  15466,  15976,  16520,  17102,  17726,  18398,  19124,
     19908,  20760,  21688,  22702,  23816,  25044,  26404,  27922,
     29622,  31540,  33720,  36222,  39116,  42502,  46514,  51334,
     57218,  64536,  73830,  85890, 101860, 123198, 151020, 183936,
    216220, 243618, 268374, 293022, 319362, 347768, 378864, 412626, 449596,
];
static hd_quantize_dither_factors_LF: [i32; 256] = [
       0,    0,    0,    1,    0,    0,    1,    1,
       0,    1,    1,    1,    1,    1,    1,    1,
       1,    1,    1,    1,    1,    1,    1,    1,
       1,    2,    1,    1,    2,    2,    2,    1,
       2,    2,    2,    2,    2,    2,    2,    2,
       2,    2,    2,    2,    2,    2,    2,    3,
       2,    3,    2,    3,    3,    3,    3,    3,
       3,    3,    3,    3,    3,    3,    3,    3,
       3,    3,    3,    3,    3,    4,    3,    4,
       4,    4,    4,    4,    4,    4,    4,    4,
       4,    4,    4,    4,    5,    4,    4,    5,
       4,    5,    5,    5,    5,    5,    5,    5,
       5,    5,    6,    5,    5,    6,    5,    6,
       6,    6,    6,    6,    6,    6,    6,    7,
       6,    7,    7,    7,    7,    7,    7,    7,
       7,    7,    8,    8,    8,    8,    8,    8,
       8,    9,    9,    9,    9,    9,    9,    9,
      10,   10,   10,   10,   10,   11,   11,   11,
      11,   11,   12,   12,   12,   12,   13,   13,
      13,   14,   14,   14,   15,   15,   15,   15,
      16,   16,   17,   17,   17,   18,   18,   18,
      19,   19,   20,   21,   21,   22,   22,   23,
      23,   24,   25,   26,   26,   27,   28,   29,
      30,   31,   32,   33,   34,   35,   36,   37,
      39,   40,   42,   43,   45,   47,   49,   51,
      53,   55,   58,   60,   63,   66,   69,   73,
      76,   80,   85,   89,   95,  100,  106,  113,
     119,  128,  136,  146,  156,  168,  182,  196,
     213,  232,  254,  279,  307,  340,  380,  425,
     480,  545,  626,  724,  847, 1003, 1205, 1471,
    1830, 2324, 3015, 3993, 5335, 6956, 8229, 8071,
    6850, 6189, 6162, 6585, 7102, 7774, 8441, 9243,
];
static hd_quantize_factor_select_offset_LF: [i16; 257] = [
      0, -22, -21, -21, -20, -20, -19, -19,
    -18, -18, -17, -17, -16, -16, -15, -14,
    -14, -13, -13, -12, -12, -11, -11, -10,
    -10,  -9,  -9,  -8,  -7,  -7,  -6,  -6,
     -5,  -5,  -4,  -4,  -3,  -3,  -2,  -1,
     -1,   0,   0,   1,   1,   2,   2,   3,
      4,   4,   5,   5,   6,   6,   7,   8,
      8,   9,   9,  10,  11,  11,  12,  12,
     13,  14,  14,  15,  15,  16,  17,  17,
     18,  19,  19,  20,  20,  21,  22,  22,
     23,  24,  24,  25,  26,  26,  27,  28,
     28,  29,  30,  30,  31,  32,  33,  33,
     34,  35,  35,  36,  37,  38,  38,  39,
     40,  41,  41,  42,  43,  44,  44,  45,
     46,  47,  48,  48,  49,  50,  51,  52,
     52,  53,  54,  55,  56,  57,  58,  58,
     59,  60,  61,  62,  63,  64,  65,  66,
     67,  68,  69,  69,  70,  71,  72,  73,
     74,  75,  77,  78,  79,  80,  81,  82,
     83,  84,  85,  86,  87,  89,  90,  91,
     92,  93,  94,  96,  97,  98,  99, 101,
    102, 103, 105, 106, 107, 109, 110, 112,
    113, 115, 116, 118, 119, 121, 122, 124,
    125, 127, 129, 130, 132, 134, 136, 137,
    139, 141, 143, 145, 147, 149, 151, 153,
    155, 158, 160, 162, 164, 167, 169, 172,
    174, 177, 180, 182, 185, 188, 191, 194,
    197, 201, 204, 208, 211, 215, 219, 223,
    227, 232, 236, 241, 246, 251, 257, 263,
    269, 275, 283, 290, 298, 307, 317, 327,
    339, 352, 367, 384, 404, 429, 458, 494,
    522, 522, 522, 522, 522, 522, 522, 522, 522,
];

// HD Quantization lookup tables for Medium-Low Frequency (MLF) band
static hd_quantize_intervals_MLF: [i32; 33] = [
      -21236,   21236,   63830,  106798,  150386,  194832,  240376,  287258,
      335726,  386034,  438460,  493308,  550924,  611696,  676082,  744626,
      817986,  896968,  982580, 1076118, 1179278, 1294344, 1424504, 1574386,
     1751090, 1966260, 2240868, 2617662, 3196432, 4176450, 5658260, 7671068,
   10380372,
];
static hd_invert_quantize_dither_factors_MLF: [i32; 33] = [
    21236,  21236,  21360,  21608,  21978,  22468,  23076,   23806,
    24660,  25648,  26778,  28070,  29544,  31228,  33158,   35386,
    37974,  41008,  44606,  48934,  54226,  60840,  69320,   80564,
    96140, 119032, 155576, 221218, 357552, 622468, 859344, 1153464, 1555840,
];
static hd_quantize_dither_factors_MLF: [i32; 32] = [
       0,   31,    62,    93,   123,   152,   183,    214,
     247,  283,   323,   369,   421,   483,   557,    647,
     759,  900,  1082,  1323,  1654,  2120,  2811,   3894,
    5723, 9136, 16411, 34084, 66229, 59219, 73530, 100594,
];
static hd_quantize_factor_select_offset_MLF: [i16; 33] = [
      0, -21, -16, -12,  -7,  -2,   3,   8,
     13,  19,  24,  30,  36,  43,  50,  57,
     65,  74,  83,  93, 104, 117, 131, 147,
    166, 189, 219, 259, 322, 427, 521, 521, 521,
];

// HD Quantization lookup tables for Medium-High Frequency (MHF) band
static hd_quantize_intervals_MHF: [i32; 9] = [
    -95044, 95044, 295844, 528780, 821332, 1226438, 1890540, 3344850, 6450664,
];
static hd_invert_quantize_dither_factors_MHF: [i32; 9] = [
    95044, 95044, 105754, 127180, 165372, 39736, 424366, 1029946, 2075866,
];
static hd_quantize_dither_factors_MHF: [i32; 8] = [
    0, 2678, 5357, 9548, -31409, 96158, 151395, 261480,
];
static hd_quantize_factor_select_offset_MHF: [i16; 9] = [
    0, -17, 5, 30, 62, 105, 177, 334, 518,
];

// HD Quantization lookup tables for High Frequency (HF) band
static hd_quantize_intervals_HF: [i32; 17] = [
     -45754,   45754,  138496,  234896,  337336,  448310,  570738,  708380,
     866534, 1053262, 1281958, 1577438, 1993050, 2665984, 3900982, 5902844,
    8897462,
];
static hd_invert_quantize_dither_factors_HF: [i32; 17] = [
    45754,  45754,  46988,  49412,  53026,  57950,  64478,   73164,
    84988, 101740, 126958, 168522, 247092, 425842, 809154, 1192708, 1801910,
];
static hd_quantize_dither_factors_HF: [i32; 16] = [
       0,  309,   606,   904,  1231,  1632,  2172,   2956,
    4188, 6305, 10391, 19643, 44688, 95828, 95889, 152301,
];
static hd_quantize_factor_select_offset_HF: [i16; 17] = [
     0, -18,  -8,   2,  13,  25,  38,  53,
    70,  90, 115, 147, 192, 264, 398, 521, 521,
];

// Quantization factors table
static quantization_factors: [i16; 32] = [
    2048, 2093, 2139, 2186, 2233, 2282, 2332, 2383,
    2435, 2489, 2543, 2599, 2656, 2714, 2774, 2834,
    2896, 2960, 3025, 3091, 3158, 3228, 3298, 3371,
    3444, 3520, 3597, 3676, 3756, 3838, 3922, 4008,
];

// QMF filter coefficient tables
static aptx_qmf_outer_coeffs: [[i32; FILTER_TAPS]; NB_FILTERS] = [
    [
        730, -413, -9611, 43626, -121026, 269973, -585547, 2801966,
        697128, -160481, 27611, 8478, -10043, 3511, 688, -897,
    ],
    [
        -897, 688, 3511, -10043, 8478, 27611, -160481, 697128,
        2801966, -585547, 269973, -121026, 43626, -9611, -413, 730,
    ],
];

static aptx_qmf_inner_coeffs: [[i32; FILTER_TAPS]; NB_FILTERS] = [
    [
       1033, -584, -13592, 61697, -171156, 381799, -828088, 3962579,
       985888, -226954, 39048, 11990, -14203, 4966, 973, -1268,
    ],
    [
      -1268, 973, 4966, -14203, 11990, 39048, -226954, 985888,
      3962579, -828088, 381799, -171156, 61697, -13592, -584, 1033,
    ],
];

// All tables array structure
static all_tables: [[aptx_tables; NB_SUBBANDS]; 2] = [
    [
        aptx_tables {
            quantize_intervals: &quantize_intervals_LF,
            invert_quantize_dither_factors: &invert_quantize_dither_factors_LF,
            quantize_dither_factors: &quantize_dither_factors_LF,
            quantize_factor_select_offset: &quantize_factor_select_offset_LF,
            tables_size: 65,
            factor_max: 0x11FF,
            prediction_order: 24,
        },
        aptx_tables {
            quantize_intervals: &quantize_intervals_MLF,
            invert_quantize_dither_factors: &invert_quantize_dither_factors_MLF,
            quantize_dither_factors: &quantize_dither_factors_MLF,
            quantize_factor_select_offset: &quantize_factor_select_offset_MLF,
            tables_size: 9,
            factor_max: 0x14FF,
            prediction_order: 12,
        },
        aptx_tables {
            quantize_intervals: &quantize_intervals_MHF,
            invert_quantize_dither_factors: &invert_quantize_dither_factors_MHF,
            quantize_dither_factors: &quantize_dither_factors_MHF,
            quantize_factor_select_offset: &quantize_factor_select_offset_MHF,
            tables_size: 3,
            factor_max: 0x16FF,
            prediction_order: 6,
        },
        aptx_tables {
            quantize_intervals: &quantize_intervals_HF,
            invert_quantize_dither_factors: &invert_quantize_dither_factors_HF,
            quantize_dither_factors: &quantize_dither_factors_HF,
            quantize_factor_select_offset: &quantize_factor_select_offset_HF,
            tables_size: 5,
            factor_max: 0x15FF,
            prediction_order: 12,
        },
    ],
    [
        aptx_tables {
            quantize_intervals: &hd_quantize_intervals_LF,
            invert_quantize_dither_factors: &hd_invert_quantize_dither_factors_LF,
            quantize_dither_factors: &hd_quantize_dither_factors_LF,
            quantize_factor_select_offset: &hd_quantize_factor_select_offset_LF,
            tables_size: 257,
            factor_max: 0x11FF,
            prediction_order: 24,
        },
        aptx_tables {
            quantize_intervals: &hd_quantize_intervals_MLF,
            invert_quantize_dither_factors: &hd_invert_quantize_dither_factors_MLF,
            quantize_dither_factors: &hd_quantize_dither_factors_MLF,
            quantize_factor_select_offset: &hd_quantize_factor_select_offset_MLF,
            tables_size: 33,
            factor_max: 0x14FF,
            prediction_order: 12,
        },
        aptx_tables {
            quantize_intervals: &hd_quantize_intervals_MHF,
            invert_quantize_dither_factors: &hd_invert_quantize_dither_factors_MHF,
            quantize_dither_factors: &hd_quantize_dither_factors_MHF,
            quantize_factor_select_offset: &hd_quantize_factor_select_offset_MHF,
            tables_size: 9,
            factor_max: 0x16FF,
            prediction_order: 6,
        },
        aptx_tables {
            quantize_intervals: &hd_quantize_intervals_HF,
            invert_quantize_dither_factors: &hd_invert_quantize_dither_factors_HF,
            quantize_dither_factors: &hd_quantize_dither_factors_HF,
            quantize_factor_select_offset: &hd_quantize_factor_select_offset_HF,
            tables_size: 17,
            factor_max: 0x15FF,
            prediction_order: 12,
        },
    ],
];

// Structs
#[derive(Debug, Clone, Copy, Default)]
pub struct aptx_filter_signal {
    pub buffer: [i32; 2 * FILTER_TAPS],
    pub pos: u8,
}

#[derive(Debug, Clone, Default)]
pub struct aptx_QMF_analysis {
    pub outer_filter_signal: [aptx_filter_signal; NB_FILTERS],
    pub inner_filter_signal: [[aptx_filter_signal; NB_FILTERS]; NB_FILTERS],
}

#[derive(Debug, Clone, Copy, Default)]
pub struct aptx_quantize {
    pub quantized_sample: i32,
    pub quantized_sample_parity_change: i32,
    pub error: i32,
}

#[derive(Debug, Clone, Copy, Default)]
pub struct aptx_invert_quantize {
    pub quantization_factor: i32,
    pub factor_select: i32,
    pub reconstructed_difference: i32,
}

#[derive(Debug, Clone)]
pub struct aptx_prediction {
    pub prev_sign: [i32; 2],
    pub s_weight: [i32; 2],
    pub d_weight: [i32; 24],
    pub pos: i32,
    pub reconstructed_differences: [i32; 48],
    pub previous_reconstructed_sample: i32,
    pub predicted_difference: i32,
    pub predicted_sample: i32,
}

impl Default for aptx_prediction {
    fn default() -> Self {
        Self {
            prev_sign: [0; 2],
            s_weight: [0; 2],
            d_weight: [0; 24],
            pos: 0,
            reconstructed_differences: [0; 48],
            previous_reconstructed_sample: 0,
            predicted_difference: 0,
            predicted_sample: 0,
        }
    }
}

#[derive(Debug, Clone, Default)]
pub struct aptx_channel {
    pub codeword_history: i32,
    pub dither_parity: i32,
    pub dither: [i32; NB_SUBBANDS],
    pub qmf: aptx_QMF_analysis,
    pub quantize: [aptx_quantize; NB_SUBBANDS],
    pub invert_quantize: [aptx_invert_quantize; NB_SUBBANDS],
    pub prediction: [aptx_prediction; NB_SUBBANDS],
}

#[derive(Debug, Clone, Default)]
pub struct aptx_context {
    pub decode_sync_packets: usize,
    pub decode_dropped: usize,
    pub channels: [aptx_channel; NB_CHANNELS],
    pub hd: u8,
    pub sync_idx: u8,
    pub encode_remaining: u8,
    pub decode_skip_leading: u8,
    pub decode_sync_buffer_len: u8,
    pub decode_sync_buffer: [u8; 6],
}

#[derive(Debug, Clone, Copy)]
pub struct aptx_tables {
    pub quantize_intervals: &'static [i32],
    pub invert_quantize_dither_factors: &'static [i32],
    pub quantize_dither_factors: &'static [i32],
    pub quantize_factor_select_offset: &'static [i16],
    pub tables_size: usize,
    pub factor_max: i32,
    pub prediction_order: usize,
}

// Function stubs

/*
 * Clip a signed integer into the -(2^p),(2^p-1) range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
#[inline]
pub fn clip_intp2(a: i32, p: u32) -> i32 {
    let a_u32 = a as u32;
    let threshold = 1u32 << p;
    let mask = !((2u32 << p).wrapping_sub(1));

    if (a_u32.wrapping_add(threshold)) & mask != 0 {
        (a >> 31) ^ ((1 << p) - 1)
    } else {
        a
    }
}

/*
 * Clip a signed integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
#[inline]
pub fn clip(a: i32, amin: i32, amax: i32) -> i32 {
    if a < amin {
        amin
    } else if a > amax {
        amax
    } else {
        a
    }
}

/*
 * Sign extension for bit manipulation
 * @param val value to sign extend
 * @param bits number of significant bits
 * @return sign extended value
 */
#[inline]
pub fn sign_extend(val: i32, bits: u32) -> i32 {
    let shift = 8 * mem::size_of::<i32>() as u32 - bits;
    let v_u = (val as u32) << shift;
    (v_u as i32) >> shift
}

/*
 * Update the codeword history used for dither generation.
 * Extracts bits from quantized samples and updates the history register.
 */
#[inline]
pub fn aptx_update_codeword_history(channel: &mut aptx_channel) {
    let cw = ((channel.quantize[0].quantized_sample & 3) << 0)
        .wrapping_add((channel.quantize[1].quantized_sample & 2) << 1)
        .wrapping_add((channel.quantize[2].quantized_sample & 1) << 3);
    channel.codeword_history = (cw << 8).wrapping_add(((channel.codeword_history as u32) << 4) as i32);
}

/*
 * Generate dither values using PRNG-like algorithm.
 * Dither is used to improve quantization and reduce artifacts.
 */
pub fn aptx_generate_dither(channel: &mut aptx_channel) {
    aptx_update_codeword_history(channel);

    let m = (5184443i64).wrapping_mul((channel.codeword_history >> 7) as i64);
    let d = ((m.wrapping_mul(4)).wrapping_add(m >> 22)) as i32;

    for subband in 0..NB_SUBBANDS {
        channel.dither[subband] = ((d as u32) << (23 - 5 * subband)) as i32;
    }
    channel.dither_parity = (d >> 25) & 1;
}

/*
 * Rounded right shift with optional clipping for 32-bit values
 */
#[inline]
fn rshift32(value: i32, shift: u32) -> i32 {
    let rounding: i32 = 1i32 << (shift - 1);
    let mask: i32 = (1i32 << (shift + 1)) - 1;
    ((value.wrapping_add(rounding)) >> shift).wrapping_sub(if (value & mask) == rounding { 1 } else { 0 })
}

#[inline]
fn rshift32_clip24(value: i32, shift: u32) -> i32 {
    clip_intp2(rshift32(value, shift), 23)
}

/*
 * Rounded right shift with optional clipping for 64-bit values
 */
#[inline]
fn rshift64(value: i64, shift: u32) -> i64 {
    let rounding: i64 = 1i64 << (shift - 1);
    let mask: i64 = (1i64 << (shift + 1)) - 1;
    ((value.wrapping_add(rounding)) >> shift).wrapping_sub(if (value & mask) == rounding { 1 } else { 0 })
}

#[inline]
fn rshift64_clip24(value: i64, shift: u32) -> i32 {
    clip_intp2(rshift64(value, shift) as i32, 23)
}

/*
 * Push one sample into a circular signal buffer.
 */
#[inline]
pub fn aptx_qmf_filter_signal_push(signal: &mut aptx_filter_signal, sample: i32) {
    let pos = signal.pos as usize;
    signal.buffer[pos] = sample;
    signal.buffer[pos + FILTER_TAPS] = sample;
    signal.pos = ((pos + 1) & (FILTER_TAPS - 1)) as u8;
}

/*
 * Compute the convolution of the signal with the coefficients, and reduce
 * to 24 bits by applying the specified right shifting.
 */
#[inline]
pub fn aptx_qmf_convolution(signal: &aptx_filter_signal, coeffs: &[i32], shift: i32) -> i32 {
    let pos = signal.pos as usize;
    let mut e: i64 = 0;

    for i in 0..FILTER_TAPS {
        e = e.wrapping_add((signal.buffer[pos + i] as i64).wrapping_mul(coeffs[i] as i64));
    }

    rshift64_clip24(e, shift as u32)
}

/*
 * Half-band QMF analysis filter realized with a polyphase FIR filter.
 * Split into 2 subbands and downsample by 2.
 * So for each pair of samples that goes in, one sample goes out,
 * split into 2 separate subbands.
 */
#[inline]
pub fn aptx_qmf_polyphase_analysis(
    signal: &mut [aptx_filter_signal; NB_FILTERS],
    coeffs: &[[i32; FILTER_TAPS]; NB_FILTERS],
    shift: u32,
    samples: &[i32],
    low_subband_output: &mut i32,
    high_subband_output: &mut i32,
) {
    let mut subbands: [i32; NB_FILTERS] = [0; NB_FILTERS];

    for i in 0..NB_FILTERS {
        aptx_qmf_filter_signal_push(&mut signal[i], samples[NB_FILTERS - 1 - i]);
        subbands[i] = aptx_qmf_convolution(&signal[i], &coeffs[i], shift as i32);
    }

    *low_subband_output = clip_intp2(subbands[0].wrapping_add(subbands[1]), 23);
    *high_subband_output = clip_intp2(subbands[0].wrapping_sub(subbands[1]), 23);
}

/*
 * Two stage QMF analysis tree.
 * Split 4 input samples into 4 subbands and downsample by 4.
 * So for each group of 4 samples that goes in, one sample goes out,
 * split into 4 separate subbands.
 */
pub fn aptx_qmf_tree_analysis(qmf: &mut aptx_QMF_analysis, samples: &[i32], subband_samples: &mut [i32]) {
    let mut intermediate_samples: [i32; 4] = [0; 4];

    // Split 4 input samples into 2 intermediate subbands downsampled to 2 samples
    for i in 0..2 {
        let mut low = 0i32;
        let mut high = 0i32;
        aptx_qmf_polyphase_analysis(
            &mut qmf.outer_filter_signal,
            &aptx_qmf_outer_coeffs,
            23,
            &samples[2 * i..],
            &mut low,
            &mut high,
        );
        intermediate_samples[0 + i] = low;
        intermediate_samples[2 + i] = high;
    }

    // Split 2 intermediate subband samples into 4 final subbands downsampled to 1 sample
    for i in 0..2 {
        let mut low = 0i32;
        let mut high = 0i32;
        aptx_qmf_polyphase_analysis(
            &mut qmf.inner_filter_signal[i],
            &aptx_qmf_inner_coeffs,
            23,
            &intermediate_samples[2 * i..],
            &mut low,
            &mut high,
        );
        subband_samples[2 * i + 0] = low;
        subband_samples[2 * i + 1] = high;
    }
}

/*
 * Half-band QMF synthesis filter realized with a polyphase FIR filter.
 * Join 2 subbands and upsample by 2.
 * So for each 2 subbands sample that goes in, a pair of samples goes out.
 */
#[inline]
pub fn aptx_qmf_polyphase_synthesis(
    signal: &mut [aptx_filter_signal; NB_FILTERS],
    coeffs: &[[i32; FILTER_TAPS]; NB_FILTERS],
    shift: u32,
    low_subband_input: i32,
    high_subband_input: i32,
    samples: &mut [i32],
) {
    let mut subbands: [i32; NB_FILTERS] = [0; NB_FILTERS];

    subbands[0] = low_subband_input.wrapping_add(high_subband_input);
    subbands[1] = low_subband_input.wrapping_sub(high_subband_input);

    for i in 0..NB_FILTERS {
        aptx_qmf_filter_signal_push(&mut signal[i], subbands[1 - i]);
        samples[i] = aptx_qmf_convolution(&signal[i], &coeffs[i], shift as i32);
    }
}

/*
 * Two stage QMF synthesis tree.
 * Join 4 subbands and upsample by 4.
 * So for each 4 subbands sample that goes in, a group of 4 samples goes out.
 */
pub fn aptx_qmf_tree_synthesis(qmf: &mut aptx_QMF_analysis, subband_samples: &[i32], samples: &mut [i32]) {
    let mut intermediate_samples: [i32; 4] = [0; 4];

    // Join 4 subbands into 2 intermediate subbands upsampled to 2 samples.
    for i in 0..2 {
        aptx_qmf_polyphase_synthesis(
            &mut qmf.inner_filter_signal[i],
            &aptx_qmf_inner_coeffs,
            22,
            subband_samples[2 * i + 0],
            subband_samples[2 * i + 1],
            &mut intermediate_samples[2 * i..],
        );
    }

    // Join 2 samples from intermediate subbands upsampled to 4 samples.
    for i in 0..2 {
        aptx_qmf_polyphase_synthesis(
            &mut qmf.outer_filter_signal,
            &aptx_qmf_outer_coeffs,
            21,
            intermediate_samples[0 + i],
            intermediate_samples[2 + i],
            &mut samples[2 * i..],
        );
    }
}

/*
 * Binary search in quantization intervals.
 * Finds the largest index where: factor * intervals[idx] <= value << 24
 */
#[inline]
pub fn aptx_bin_search(value: i32, factor: i32, intervals: &[i32], nb_intervals: i32) -> i32 {
    let mut idx: i32 = 0;
    let mut i = nb_intervals >> 1;

    while i > 0 {
        if (factor as i64).wrapping_mul(intervals[(idx + i) as usize] as i64) <= ((value as i64) << 24) {
            idx = idx.wrapping_add(i);
        }
        i >>= 1;
    }

    idx
}

/*
 * Quantize a sample difference for encoding.
 * Uses binary search in quantization intervals and applies dithering.
 */
pub fn aptx_quantize_difference(
    quantize: &mut aptx_quantize,
    sample_difference: i32,
    dither: i32,
    quantization_factor: i32,
    tables: &aptx_tables,
) {
    let intervals = tables.quantize_intervals;
    let mut sample_difference_abs: i32 = sample_difference;

    // Compute absolute value
    if sample_difference_abs < 0 {
        sample_difference_abs = sample_difference_abs.wrapping_neg();
    }

    // Clip to 24-bit range
    if sample_difference_abs > ((1i32 << 23) - 1) {
        sample_difference_abs = (1i32 << 23) - 1;
    }

    // Binary search to find quantized sample
    let mut quantized_sample = aptx_bin_search(
        sample_difference_abs >> 4,
        quantization_factor,
        intervals,
        tables.tables_size as i32,
    );

    // Calculate dithered reconstruction
    let d = rshift32_clip24(
        ((dither as i64).wrapping_mul(dither as i64) >> 32) as i32,
        7
    ).wrapping_sub((1i32 << 23));

    let d = rshift64(
        (d as i64).wrapping_mul(tables.quantize_dither_factors[quantized_sample as usize] as i64),
        23
    ) as i32;

    let intervals_ptr = &intervals[quantized_sample as usize..];
    let mean = (intervals_ptr[1].wrapping_add(intervals_ptr[0])) / 2;
    let interval = (intervals_ptr[1].wrapping_sub(intervals_ptr[0]))
        .wrapping_mul(if sample_difference < 0 { -1 } else { 1 });

    let dithered_sample = rshift64_clip24(
        (dither as i64).wrapping_mul(interval as i64)
            .wrapping_add((clip_intp2(mean.wrapping_add(d), 23) as i64) << 32),
        32
    );

    // Calculate quantization error
    let error = ((sample_difference_abs as i64) << 20)
        .wrapping_sub((dithered_sample as i64).wrapping_mul(quantization_factor as i64));

    quantize.error = rshift64(error, 23) as i32;
    if quantize.error < 0 {
        quantize.error = quantize.error.wrapping_neg();
    }

    // Adjust quantized sample based on error direction
    let mut parity_change = quantized_sample;
    if error < 0 {
        quantized_sample = quantized_sample.wrapping_sub(1);
    } else {
        parity_change = parity_change.wrapping_sub(1);
    }

    // Apply sign inversion mask
    let inv = if sample_difference < 0 { -1 } else { 0 };
    quantize.quantized_sample = quantized_sample ^ inv;
    quantize.quantized_sample_parity_change = parity_change ^ inv;
}

/*
 * Encode a channel (processes all subbands).
 * This is the main encoding function that:
 * 1. Analyzes input samples into subbands using QMF tree
 * 2. Generates dither for the channel
 * 3. Quantizes each subband difference
 */
pub fn aptx_encode_channel(channel: &mut aptx_channel, samples: &[i32], hd: i32) {
    let mut subband_samples: [i32; NB_SUBBANDS] = [0; NB_SUBBANDS];

    aptx_qmf_tree_analysis(&mut channel.qmf, samples, &mut subband_samples);
    aptx_generate_dither(channel);

    for subband in 0..NB_SUBBANDS {
        let diff = clip_intp2(
            subband_samples[subband].wrapping_sub(channel.prediction[subband].predicted_sample),
            23
        );
        aptx_quantize_difference(
            &mut channel.quantize[subband],
            diff,
            channel.dither[subband],
            channel.invert_quantize[subband].quantization_factor,
            &all_tables[hd as usize][subband],
        );
    }
}

/*
 * Decode a channel (reconstructs samples from quantized values).
 * Uses the QMF synthesis tree to reconstruct the output samples from subband data.
 */
pub fn aptx_decode_channel(channel: &mut aptx_channel, samples: &mut [i32]) {
    let mut subband_samples: [i32; NB_SUBBANDS] = [0; NB_SUBBANDS];

    for subband in 0..NB_SUBBANDS {
        subband_samples[subband] = channel.prediction[subband].previous_reconstructed_sample;
    }
    aptx_qmf_tree_synthesis(&mut channel.qmf, &subband_samples, samples);
}

/*
 * Inverse quantization used in decoding.
 * Reconstructs the difference from the quantized sample value.
 */
pub fn aptx_invert_quantization(
    invert_quantize: &mut aptx_invert_quantize,
    quantized_sample: i32,
    dither: i32,
    tables: &aptx_tables,
) {
    let mut idx = (quantized_sample ^ (if quantized_sample < 0 { -1 } else { 0 })).wrapping_add(1);
    let mut qr = tables.quantize_intervals[idx as usize] / 2;
    if quantized_sample < 0 {
        qr = -qr;
    }

    qr = rshift64_clip24(
        ((qr as i64) << 32).wrapping_add((dither as i64).wrapping_mul(tables.invert_quantize_dither_factors[idx as usize] as i64)),
        32
    );
    invert_quantize.reconstructed_difference = ((invert_quantize.quantization_factor as i64).wrapping_mul(qr as i64) >> 19) as i32;

    // update factor_select
    let mut factor_select = (32620i32).wrapping_mul(invert_quantize.factor_select);
    factor_select = rshift32(
        factor_select.wrapping_add((tables.quantize_factor_select_offset[idx as usize] as i32).wrapping_mul(1 << 15)),
        15
    );
    invert_quantize.factor_select = clip(factor_select, 0, tables.factor_max);

    // update quantization factor
    idx = (invert_quantize.factor_select & 0xFF) >> 3;
    let shift = (tables.factor_max - invert_quantize.factor_select) >> 8;
    invert_quantize.quantization_factor = (quantization_factors[idx as usize] as i32) << 11 >> shift;
}

/*
 * Helper function to update reconstructed differences circular buffer.
 */
fn aptx_reconstructed_differences_update(
    prediction: &mut aptx_prediction,
    reconstructed_difference: i32,
    order: i32,
) -> usize {
    let order_usize = order as usize;
    let p = prediction.pos as usize;

    prediction.reconstructed_differences[p] = prediction.reconstructed_differences[order_usize + p];
    prediction.pos = ((p + 1) % order_usize) as i32;
    let new_p = prediction.pos as usize;
    prediction.reconstructed_differences[order_usize + new_p] = reconstructed_difference;
    order_usize + new_p
}

/*
 * Prediction filtering for adaptive decoding.
 * Uses adaptive weight updates to predict the next sample.
 */
pub fn aptx_prediction_filtering(
    prediction: &mut aptx_prediction,
    reconstructed_difference: i32,
    order: i32,
) {
    let reconstructed_sample = clip_intp2(
        reconstructed_difference.wrapping_add(prediction.predicted_sample),
        23
    );
    let predictor = clip_intp2(
        (((prediction.s_weight[0] as i64).wrapping_mul(prediction.previous_reconstructed_sample as i64)
            .wrapping_add((prediction.s_weight[1] as i64).wrapping_mul(reconstructed_sample as i64))) >> 22) as i32,
        23
    );
    prediction.previous_reconstructed_sample = reconstructed_sample;

    let rd_idx = aptx_reconstructed_differences_update(prediction, reconstructed_difference, order);
    let srd0 = ((if reconstructed_difference > 0 { 1i32 } else { 0i32 }).wrapping_sub(if reconstructed_difference < 0 { 1i32 } else { 0i32 }))
        .wrapping_mul(1i32 << 23);

    let mut predicted_difference: i64 = 0;
    for i in 0..(order as usize) {
        let srd = (prediction.reconstructed_differences[rd_idx.wrapping_sub(i + 1)] >> 31) | 1;
        prediction.d_weight[i] = prediction.d_weight[i].wrapping_sub(rshift32(
            prediction.d_weight[i].wrapping_sub(srd.wrapping_mul(srd0)),
            8
        ));
        predicted_difference = predicted_difference.wrapping_add(
            (prediction.reconstructed_differences[rd_idx.wrapping_sub(i)] as i64)
                .wrapping_mul(prediction.d_weight[i] as i64)
        );
    }

    prediction.predicted_difference = clip_intp2((predicted_difference >> 22) as i32, 23);
    prediction.predicted_sample = clip_intp2(
        predictor.wrapping_add(prediction.predicted_difference),
        23
    );
}

/*
 * Process a subband (combines inversion and prediction).
 * Performs inverse quantization and updates prediction weights.
 */
pub fn aptx_process_subband(
    invert_quantize: &mut aptx_invert_quantize,
    prediction: &mut aptx_prediction,
    quantized_sample: i32,
    dither: i32,
    tables: &aptx_tables,
) {
    aptx_invert_quantization(invert_quantize, quantized_sample, dither, tables);

    let sign = ((if invert_quantize.reconstructed_difference > (prediction.predicted_difference.wrapping_neg()) { 1i32 } else { 0i32 })
        .wrapping_sub(if invert_quantize.reconstructed_difference < (prediction.predicted_difference.wrapping_neg()) { 1i32 } else { 0i32 }));

    let same_sign_0 = sign.wrapping_mul(prediction.prev_sign[0]);
    let same_sign_1 = sign.wrapping_mul(prediction.prev_sign[1]);
    prediction.prev_sign[0] = prediction.prev_sign[1];
    prediction.prev_sign[1] = sign | 1;

    let mut range = 0x100000i32;
    let sw1 = rshift32((same_sign_1.wrapping_neg()).wrapping_mul(prediction.s_weight[1]), 1);
    let sw1 = (clip(sw1, -range, range) & !0xF).wrapping_mul(16);

    range = 0x300000;
    let weight_0 = (254i32).wrapping_mul(prediction.s_weight[0])
        .wrapping_add((0x800000i32).wrapping_mul(same_sign_0))
        .wrapping_add(sw1);
    prediction.s_weight[0] = clip(rshift32(weight_0, 8), -range, range);

    range = (0x3C0000i32).wrapping_sub(prediction.s_weight[0]);
    let weight_1 = (255i32).wrapping_mul(prediction.s_weight[1])
        .wrapping_add((0xC00000i32).wrapping_mul(same_sign_1));
    prediction.s_weight[1] = clip(rshift32(weight_1, 8), -range, range);

    aptx_prediction_filtering(
        prediction,
        invert_quantize.reconstructed_difference,
        tables.prediction_order as i32,
    );
}

/*
 * Invert quantization and apply prediction for all subbands.
 * This function processes all subbands in sequence after decoding.
 */
pub fn aptx_invert_quantize_and_prediction(channel: &mut aptx_channel, hd: i32) {
    for subband in 0..NB_SUBBANDS {
        let quantized_sample = channel.quantize[subband].quantized_sample;
        let dither = channel.dither[subband];
        aptx_process_subband(
            &mut channel.invert_quantize[subband],
            &mut channel.prediction[subband],
            quantized_sample,
            dither,
            &all_tables[hd as usize][subband],
        );
    }
}

/*
 * Calculate the parity of quantized samples in a channel.
 * The parity is computed by XORing the dither_parity with all quantized samples.
 */
pub fn aptx_quantized_parity(channel: &aptx_channel) -> i32 {
    let mut parity = channel.dither_parity;

    for subband in 0..NB_SUBBANDS {
        parity ^= channel.quantize[subband].quantized_sample;
    }

    parity & 1
}

/*
 * For each sample, ensure that the parity of all subbands of all channels
 * is 0 except once every 8 samples where the parity is forced to 1.
 */
pub fn aptx_check_parity(channels: &[aptx_channel; NB_CHANNELS], sync_idx: &mut u8) -> i32 {
    const LEFT: usize = 0;
    const RIGHT: usize = 1;

    let parity = aptx_quantized_parity(&channels[LEFT])
               ^ aptx_quantized_parity(&channels[RIGHT]);
    let eighth = if *sync_idx == 7 { 1 } else { 0 };

    *sync_idx = (*sync_idx + 1) & 7;
    parity ^ eighth
}

/*
 * Insert synchronization by adjusting parity if needed.
 * If parity check indicates correction is needed, find the quantized sample
 * with the smallest error and adjust it to force the desired parity.
 */
pub fn aptx_insert_sync(channels: &mut [aptx_channel; NB_CHANNELS], sync_idx: &mut u8) {
    const MAP: [usize; 4] = [1, 2, 0, 3];

    if aptx_check_parity(channels, sync_idx) != 0 {
        // Find the quantize with minimum error
        let mut min_error = channels[NB_CHANNELS - 1].quantize[MAP[0]].error;
        let mut min_channel = NB_CHANNELS - 1;
        let mut min_subband = MAP[0];

        for c in (0..NB_CHANNELS).rev() {
            for i in 0..NB_SUBBANDS {
                if channels[c].quantize[MAP[i]].error < min_error {
                    min_error = channels[c].quantize[MAP[i]].error;
                    min_channel = c;
                    min_subband = MAP[i];
                }
            }
        }

        /*
         * Forcing the desired parity is done by offsetting by 1 the quantized
         * sample from the subband featuring the smallest quantization error.
         */
        channels[min_channel].quantize[min_subband].quantized_sample =
            channels[min_channel].quantize[min_subband].quantized_sample_parity_change;
    }
}

/*
 * Pack quantized samples into 16-bit aptX codeword.
 * The codeword layout is:
 *   bits 13-15: HF subband (3 bits) with parity
 *   bits 11-12: MHF subband (2 bits)
 *   bits 7-10:  MLF subband (4 bits)
 *   bits 0-6:   LF subband (7 bits)
 */
pub fn aptx_pack_codeword(channel: &aptx_channel) -> u16 {
    let parity = aptx_quantized_parity(channel);
    ((((channel.quantize[3].quantized_sample & 0x06) | parity) << 13)
   | (((channel.quantize[2].quantized_sample & 0x03)         ) << 11)
   | (((channel.quantize[1].quantized_sample & 0x0F)         ) <<  7)
   | (((channel.quantize[0].quantized_sample & 0x7F)         ) <<  0)) as u16
}

/*
 * Pack quantized samples into 24-bit aptX HD codeword.
 * The codeword layout is:
 *   bits 19-23: HF subband (5 bits) with parity
 *   bits 15-18: MHF subband (4 bits)
 *   bits 9-14:  MLF subband (6 bits)
 *   bits 0-8:   LF subband (9 bits)
 */
pub fn aptxhd_pack_codeword(channel: &aptx_channel) -> u32 {
    let parity = aptx_quantized_parity(channel);
    ((((channel.quantize[3].quantized_sample & 0x01E) | parity) << 19)
   | (((channel.quantize[2].quantized_sample & 0x00F)         ) << 15)
   | (((channel.quantize[1].quantized_sample & 0x03F)         ) <<  9)
   | (((channel.quantize[0].quantized_sample & 0x1FF)         ) <<  0)) as u32
}

/*
 * Unpack 16-bit aptX codeword into quantized samples.
 * The codeword is split into 4 subbands with sign extension.
 * The HF subband parity bit is replaced with the calculated parity.
 */
pub fn aptx_unpack_codeword(channel: &mut aptx_channel, codeword: u16) {
    channel.quantize[0].quantized_sample = sign_extend((codeword >>  0) as i32, 7);
    channel.quantize[1].quantized_sample = sign_extend((codeword >>  7) as i32, 4);
    channel.quantize[2].quantized_sample = sign_extend((codeword >> 11) as i32, 2);
    channel.quantize[3].quantized_sample = sign_extend((codeword >> 13) as i32, 3);
    channel.quantize[3].quantized_sample = (channel.quantize[3].quantized_sample & !1)
                                          | aptx_quantized_parity(channel);
}

/*
 * Unpack 24-bit aptX HD codeword into quantized samples.
 * The codeword is split into 4 subbands with sign extension.
 * The HF subband parity bit is replaced with the calculated parity.
 */
pub fn aptxhd_unpack_codeword(channel: &mut aptx_channel, codeword: u32) {
    channel.quantize[0].quantized_sample = sign_extend((codeword >>  0) as i32, 9);
    channel.quantize[1].quantized_sample = sign_extend((codeword >>  9) as i32, 6);
    channel.quantize[2].quantized_sample = sign_extend((codeword >> 15) as i32, 4);
    channel.quantize[3].quantized_sample = sign_extend((codeword >> 19) as i32, 5);
    channel.quantize[3].quantized_sample = (channel.quantize[3].quantized_sample & !1)
                                          | aptx_quantized_parity(channel);
}

/*
 * Encode 8 PCM samples (4 per channel) into codewords.
 * For each channel: analyzes samples, generates dither, quantizes differences,
 * inverts quantization for prediction, and packs into codeword bytes.
 */
pub fn aptx_encode_samples(ctx: &mut aptx_context, samples: &[[i32; 4]; NB_CHANNELS], output: &mut [u8]) {
    // Encode both channels
    for channel in 0..NB_CHANNELS {
        aptx_encode_channel(&mut ctx.channels[channel], &samples[channel], ctx.hd as i32);
    }

    // Insert sync pattern
    aptx_insert_sync(&mut ctx.channels, &mut ctx.sync_idx);

    // Invert quantization and pack codewords
    for channel in 0..NB_CHANNELS {
        aptx_invert_quantize_and_prediction(&mut ctx.channels[channel], ctx.hd as i32);
        if ctx.hd != 0 {
            let codeword = aptxhd_pack_codeword(&ctx.channels[channel]);
            output[3 * channel + 0] = ((codeword >> 16) & 0xFF) as u8;
            output[3 * channel + 1] = ((codeword >>  8) & 0xFF) as u8;
            output[3 * channel + 2] = ((codeword >>  0) & 0xFF) as u8;
        } else {
            let codeword = aptx_pack_codeword(&ctx.channels[channel]);
            output[2 * channel + 0] = ((codeword >> 8) & 0xFF) as u8;
            output[2 * channel + 1] = ((codeword >> 0) & 0xFF) as u8;
        }
    }
}

/*
 * Decode codewords into 8 PCM samples (4 per channel).
 * Returns non-zero if parity check failed (corrupted data).
 */
pub fn aptx_decode_samples(ctx: &mut aptx_context, input: &[u8], samples: &mut [[i32; 4]; NB_CHANNELS]) -> i32 {
    // Generate dither and unpack codewords for both channels
    for channel in 0..NB_CHANNELS {
        aptx_generate_dither(&mut ctx.channels[channel]);

        if ctx.hd != 0 {
            aptxhd_unpack_codeword(
                &mut ctx.channels[channel],
                ((input[3 * channel + 0] as u32) << 16) |
                ((input[3 * channel + 1] as u32) <<  8) |
                ((input[3 * channel + 2] as u32) <<  0)
            );
        } else {
            aptx_unpack_codeword(
                &mut ctx.channels[channel],
                (((input[2 * channel + 0] as u16) << 8) |
                 ((input[2 * channel + 1] as u16) << 0))
            );
        }
        aptx_invert_quantize_and_prediction(&mut ctx.channels[channel], ctx.hd as i32);
    }

    // Check parity
    let ret = aptx_check_parity(&ctx.channels, &mut ctx.sync_idx);

    // Decode both channels
    for channel in 0..NB_CHANNELS {
        aptx_decode_channel(&mut ctx.channels[channel], &mut samples[channel]);
    }

    ret
}

/*
 * Reset decode synchronization state (preserving sync buffer).
 */
pub fn aptx_reset_decode_sync(ctx: &mut aptx_context) {
    let decode_dropped = ctx.decode_dropped;
    let decode_sync_packets = ctx.decode_sync_packets;
    let decode_sync_buffer_len = ctx.decode_sync_buffer_len;
    let mut decode_sync_buffer = [0u8; 6];

    for i in 0..6 {
        decode_sync_buffer[i] = ctx.decode_sync_buffer[i];
    }

    aptx_reset(ctx);

    for i in 0..6 {
        ctx.decode_sync_buffer[i] = decode_sync_buffer[i];
    }

    ctx.decode_sync_buffer_len = decode_sync_buffer_len;
    ctx.decode_sync_packets = decode_sync_packets;
    ctx.decode_dropped = decode_dropped;
}

/*
 * Reset all codec state to initial values.
 * Preserves the HD mode flag.
 */
pub fn aptx_reset(ctx: &mut aptx_context) {
    let hd = ctx.hd;

    // Zero out entire context (using mem::size_of instead of direct byte manipulation)
    *ctx = aptx_context::default();

    ctx.hd = hd;
    ctx.decode_skip_leading = ((LATENCY_SAMPLES + 3) / 4) as u8;
    ctx.encode_remaining = ((LATENCY_SAMPLES + 3) / 4) as u8;

    // Initialize prediction signs to 1
    for chan in 0..NB_CHANNELS {
        for subband in 0..NB_SUBBANDS {
            ctx.channels[chan].prediction[subband].prev_sign[0] = 1;
            ctx.channels[chan].prediction[subband].prev_sign[1] = 1;
        }
    }
}

/*
 * Cleanup/deallocate context.
 * In Rust, this is handled by Drop trait when Box goes out of scope.
 * This function is provided for C API compatibility but does nothing.
 */
pub fn aptx_finish(_ctx: Box<aptx_context>) {
    // In Rust, the Box will be automatically dropped and memory freed
    // when this function returns and the Box goes out of scope.
    // No explicit cleanup needed.
}

/*
 * Allocate and initialize aptX context.
 * Returns None on allocation failure (though Box::new typically panics on OOM).
 */
pub fn aptx_init(hd: i32) -> Option<Box<aptx_context>> {
    let mut ctx = Box::new(aptx_context::default());

    ctx.hd = if hd != 0 { 1 } else { 0 };

    aptx_reset(&mut ctx);
    Some(ctx)
}

/*
 * Main encode function with buffering.
 * Encodes PCM samples from input buffer into aptX codewords in output buffer.
 * Returns number of input bytes consumed.
 */
pub fn aptx_encode(
    ctx: &mut aptx_context,
    input: &[u8],
    input_size: usize,
    output: &mut [u8],
    output_size: usize,
    written: &mut usize,
) -> usize {
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let mut samples: [[i32; 4]; NB_CHANNELS] = [[0; 4]; NB_CHANNELS];
    let mut ipos: usize = 0;
    let mut opos: usize = 0;

    while ipos + 3 * NB_CHANNELS * 4 <= input_size && opos + sample_size <= output_size {
        // Read 4 samples per channel (8 samples total)
        for sample in 0..4 {
            for channel in 0..NB_CHANNELS {
                // samples need to contain 24bit signed integer stored as 32bit signed integers
                // last int8_t -> uint32_t cast propagates signedness for 32bit integer
                samples[channel][sample] =
                    ((input[ipos + 0] as u32) <<  0) as i32 |
                    ((input[ipos + 1] as u32) <<  8) as i32 |
                    ((input[ipos + 2] as i8 as i32) << 16);
                ipos += 3;
            }
        }

        aptx_encode_samples(ctx, &samples, &mut output[opos..]);
        opos += sample_size;
    }

    *written = opos;
    ipos
}

/*
 * Finish encoding and flush remaining samples.
 * Encodes latency padding with zero samples.
 * Returns 1 if complete, 0 if more output buffer space needed.
 */
pub fn aptx_encode_finish(
    ctx: &mut aptx_context,
    output: &mut [u8],
    output_size: usize,
    written: &mut usize,
) -> i32 {
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let samples: [[i32; 4]; NB_CHANNELS] = [[0; 4]; NB_CHANNELS];
    let mut opos: usize = 0;

    if ctx.encode_remaining == 0 {
        *written = 0;
        return 1;
    }

    while ctx.encode_remaining > 0 && opos + sample_size <= output_size {
        aptx_encode_samples(ctx, &samples, &mut output[opos..]);
        ctx.encode_remaining -= 1;
        opos += sample_size;
    }

    *written = opos;

    if ctx.encode_remaining > 0 {
        return 0;
    }

    aptx_reset(ctx);
    1
}

/*
 * Main decode function with buffering.
 * Decodes aptX codewords from input buffer into PCM samples in output buffer.
 * Returns number of input bytes consumed.
 */
pub fn aptx_decode(
    ctx: &mut aptx_context,
    input: &[u8],
    input_size: usize,
    output: &mut [u8],
    output_size: usize,
    written: &mut usize,
) -> usize {
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let mut samples: [[i32; 4]; NB_CHANNELS] = [[0; 4]; NB_CHANNELS];
    let mut ipos: usize = 0;
    let mut opos: usize = 0;

    while ipos + sample_size <= input_size &&
          (opos + 3 * NB_CHANNELS * 4 <= output_size || ctx.decode_skip_leading > 0) {
        if aptx_decode_samples(ctx, &input[ipos..], &mut samples) != 0 {
            break;
        }

        let mut sample_start = 0;
        if ctx.decode_skip_leading > 0 {
            ctx.decode_skip_leading -= 1;
            if ctx.decode_skip_leading > 0 {
                ipos += sample_size;
                continue;
            }
            sample_start = LATENCY_SAMPLES % 4;
        }

        for sample in sample_start..4 {
            for channel in 0..NB_CHANNELS {
                // samples contain 24bit signed integers stored as 32bit signed integers
                // we do not need to care about negative integers specially as they have 23th bit set
                output[opos + 0] = (((samples[channel][sample] as u32) >>  0) & 0xFF) as u8;
                output[opos + 1] = (((samples[channel][sample] as u32) >>  8) & 0xFF) as u8;
                output[opos + 2] = (((samples[channel][sample] as u32) >> 16) & 0xFF) as u8;
                opos += 3;
            }
        }

        ipos += sample_size;
    }

    *written = opos;
    ipos
}

/*
 * Decode with auto-synchronization for corrupted streams.
 * Attempts to resynchronize after detecting parity errors.
 * Returns number of input bytes consumed.
 */
pub fn aptx_decode_sync(
    ctx: &mut aptx_context,
    input: &[u8],
    input_size: usize,
    output: &mut [u8],
    output_size: usize,
    written: &mut usize,
    synced: &mut i32,
    dropped: &mut usize,
) -> usize {
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let mut ipos: usize = 0;
    let mut opos: usize = 0;

    *synced = 0;
    *dropped = 0;

    // If we have some unprocessed bytes in internal cache, first fill remaining data to internal cache except the final byte
    if ctx.decode_sync_buffer_len > 0 && sample_size - 1 - (ctx.decode_sync_buffer_len as usize) <= input_size {
        while (ctx.decode_sync_buffer_len as usize) < sample_size - 1 {
            ctx.decode_sync_buffer[ctx.decode_sync_buffer_len as usize] = input[ipos];
            ctx.decode_sync_buffer_len += 1;
            ipos += 1;
        }
    }

    // Internal cache decode loop, use it only when sample is split between internal cache and input buffer
    while ctx.decode_sync_buffer_len == (sample_size - 1) as u8 &&
          ipos < sample_size && ipos < input_size &&
          (opos + 3 * NB_CHANNELS * 4 <= output_size || ctx.decode_skip_leading > 0 || ctx.decode_dropped > 0) {
        ctx.decode_sync_buffer[sample_size - 1] = input[ipos];
        ipos += 1;

        // Copy buffer to avoid borrow conflicts
        let mut decode_buffer = [0u8; 6];
        for i in 0..sample_size {
            decode_buffer[i] = ctx.decode_sync_buffer[i];
        }

        let mut written_step: usize = 0;
        let processed_step = aptx_decode(
            ctx,
            &decode_buffer[..sample_size],
            sample_size,
            &mut output[opos..],
            output_size - opos,
            &mut written_step
        );

        opos += written_step;

        if ctx.decode_dropped > 0 && processed_step == sample_size {
            ctx.decode_dropped += processed_step;
            ctx.decode_sync_packets += 1;
            if ctx.decode_sync_packets >= (LATENCY_SAMPLES + 3) / 4 {
                *dropped += ctx.decode_dropped;
                ctx.decode_dropped = 0;
                ctx.decode_sync_packets = 0;
            }
        }

        if processed_step < sample_size {
            aptx_reset_decode_sync(ctx);
            *synced = 0;
            ctx.decode_dropped += 1;
            ctx.decode_sync_packets = 0;
            for i in 0..(sample_size - 1) {
                ctx.decode_sync_buffer[i] = ctx.decode_sync_buffer[i + 1];
            }
        } else {
            if ctx.decode_dropped == 0 {
                *synced = 1;
            }
            ctx.decode_sync_buffer_len = 0;
        }
    }

    // If all unprocessed data are now available only in input buffer, do not use internal cache
    if ctx.decode_sync_buffer_len == (sample_size - 1) as u8 && ipos == sample_size {
        ipos = 0;
        ctx.decode_sync_buffer_len = 0;
    }

    // Main decode loop, decode as much as possible samples, if decoding fails restart it on next byte
    while ipos + sample_size <= input_size &&
          (opos + 3 * NB_CHANNELS * 4 <= output_size || ctx.decode_skip_leading > 0 || ctx.decode_dropped > 0) {
        let mut input_size_step = (((output_size - opos) / (3 * NB_CHANNELS * 4)) + (ctx.decode_skip_leading as usize)) * sample_size;
        if input_size_step > ((input_size - ipos) / sample_size) * sample_size {
            input_size_step = ((input_size - ipos) / sample_size) * sample_size;
        }
        if input_size_step > (((LATENCY_SAMPLES + 3) / 4) - ctx.decode_sync_packets) * sample_size && ctx.decode_dropped > 0 {
            input_size_step = (((LATENCY_SAMPLES + 3) / 4) - ctx.decode_sync_packets) * sample_size;
        }

        let mut written_step: usize = 0;
        let processed_step = aptx_decode(
            ctx,
            &input[ipos..],
            input_size_step,
            &mut output[opos..],
            output_size - opos,
            &mut written_step
        );

        ipos += processed_step;
        opos += written_step;

        if ctx.decode_dropped > 0 && processed_step / sample_size > 0 {
            ctx.decode_dropped += processed_step;
            ctx.decode_sync_packets += processed_step / sample_size;
            if ctx.decode_sync_packets >= (LATENCY_SAMPLES + 3) / 4 {
                *dropped += ctx.decode_dropped;
                ctx.decode_dropped = 0;
                ctx.decode_sync_packets = 0;
            }
        }

        if processed_step < input_size_step {
            aptx_reset_decode_sync(ctx);
            *synced = 0;
            ipos += 1;
            ctx.decode_dropped += 1;
            ctx.decode_sync_packets = 0;
        } else if ctx.decode_dropped == 0 {
            *synced = 1;
        }
    }

    // If number of unprocessed bytes is less then sample size store them to internal cache
    if ipos + sample_size > input_size {
        while ipos < input_size {
            ctx.decode_sync_buffer[ctx.decode_sync_buffer_len as usize] = input[ipos];
            ctx.decode_sync_buffer_len += 1;
            ipos += 1;
        }
    }

    *written = opos;
    ipos
}

/*
 * Finish synchronized decoding.
 * Returns number of bytes dropped from sync buffer.
 */
pub fn aptx_decode_sync_finish(ctx: &mut aptx_context) -> usize {
    let dropped = ctx.decode_sync_buffer_len as usize;
    aptx_reset(ctx);
    dropped
}
