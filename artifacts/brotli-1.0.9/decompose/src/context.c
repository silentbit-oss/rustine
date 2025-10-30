typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
/*** DEPENDENCIES:
***/


