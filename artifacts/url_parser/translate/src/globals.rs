use crate::*;

pub const CHAR_CAT: [u16; 256] = [
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 8 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 16 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 24 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 32 elements
    0x000, 0x0d8, 0x000, 0x004, 0x0d8, 0x0d0, 0x0d8, 0x0d8, // 40 elements
    0x0d8, 0x0d8, 0x0d8, 0x0d9, 0x0d8, 0x0d3, 0x0d3, 0x054, // 48 elements
    0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, // 56 elements
    0x1ff, 0x1ff, 0x1d4, 0x0d8, 0x000, 0x0d8, 0x000, 0x044, // 64 elements
    0x054, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x0df, // 72 elements
    0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, // 80 elements
    0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, // 88 elements
    0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x000, 0x000, 0x004, // 96 elements
    0x000, 0x0d2, 0x000, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, // 104 elements
    0x1ff, 0x1ff, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, // 112 elements
    0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, // 120 elements
    0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, // 128 elements
    0x0df, 0x0d2, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 136 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 144 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 152 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 160 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 168 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 176 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 184 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 192 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 200 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 208 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 216 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 224 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 232 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 240 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 248 elements
    0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, // 256 elements
];

// Define the alphanumeric characters as a constant string slice in Rust
pub const ALNUM: &str = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

fn main() {
    // Example usage of the ALNUM constant
    println!("{}", ALNUM);
}

pub const unreserved: &str = "-._~";

pub const subdelim: &str = "!$&'()*+,;=";

pub const URL_SCHEMES: [&str; 181] = [
    "aaa", // 1
    "aaas", // 2
    "about", // 3
    "acap", // 4
    "acct", // 5
    "adiumxtra", // 6
    "afp", // 7
    "afs", // 8
    "aim", // 9
    "apt", // 10
    "attachment", // 11
    "aw", // 12
    "beshare", // 13
    "bitcoin", // 14
    "bolo", // 15
    "callto", // 16
    "cap", // 17
    "chrome", // 18
    "crome-extension", // 19
    "com-evenbrite-attendee", // 20
    "cid", // 21
    "coap", // 22
    "coaps", // 23
    "content", // 24
    "crid", // 25
    "cvs", // 26
    "data", // 27
    "dav", // 28
    "dict", // 29
    "lna-playsingle", // 30
    "dln-playcontainer", // 31
    "dns", // 32
    "dtn", // 33
    "dvb", // 34
    "ed2k", // 35
    "facetime", // 36
    "fax", // 37
    "feed", // 38
    "file", // 39
    "finger", // 40
    "fish", // 41
    "ftp", // 42
    "geo", // 43
    "gg", // 44
    "git", // 45
    "gizmoproject", // 46
    "go", // 47
    "gopher", // 48
    "gtalk", // 49
    "h323", // 50
    "hcp", // 51
    "http", // 52
    "https", // 53
    "iax", // 54
    "icap", // 55
    "icon", // 56
    "im", // 57
    "imap", // 58
    "info", // 59
    "ipn", // 60
    "ipp", // 61
    "irc", // 62
    "irc6", // 63
    "ircs", // 64
    "iris", // 65
    "iris.beep", // 66
    "iris.xpc", // 67
    "iris.xpcs", // 68
    "iris.lws", // 69
    "itms", // 70
    "jabber", // 71
    "jar", // 72
    "jms", // 73
    "keyparc", // 74
    "lastfm", // 75
    "ldap", // 76
    "ldaps", // 77
    "magnet", // 78
    "mailserver", // 79
    "mailto", // 80
    "maps", // 81
    "market", // 82
    "message", // 83
    "mid", // 84
    "mms", // 85
    "modem", // 86
    "ms-help", // 87
    "mssettings-power", // 88
    "msnim", // 89
    "msrp", // 90
    "msrps", // 91
    "mtqp", // 92
    "mumble", // 93
    "mupdate", // 94
    "mvn", // 95
    "news", // 96
    "nfs", // 97
    "ni", // 98
    "nih", // 99
    "nntp", // 100
    "notes", // 101
    "oid", // 102
    "paquelocktoken", // 103
    "pack", // 104
    "palm", // 105
    "paparazzi", // 106
    "pkcs11", // 107
    "platform", // 108
    "pop", // 109
    "pres", // 110
    "prospero", // 111
    "proxy", // 112
    "psyc", // 113
    "query", // 114
    "reload", // 115
    "res", // 116
    "resource", // 117
    "rmi", // 118
    "rsync", // 119
    "rtmp", // 120
    "rtsp", // 121
    "secondlife", // 122
    "service", // 123
    "session", // 124
    "sftp", // 125
    "sgn", // 126
    "shttp", // 127
    "sieve", // 128
    "sip", // 129
    "sips", // 130
    "skype", // 131
    "smb", // 132
    "sms", // 133
    "snews", // 134
    "snmp", // 135
    "soap.beep", // 136
    "soap.beeps", // 137
    "soldat", // 138
    "spotify", // 139
    "ssh", // 140
    "steam", // 141
    "svn", // 142
    "tag", // 143
    "teamspeak", // 144
    "tel", // 145
    "telnet", // 146
    "tftp", // 147
    "things", // 148
    "thismessage", // 149
    "tn3270", // 150
    "tip", // 151
    "tv", // 152
    "udp", // 153
    "unreal", // 154
    "urn", // 155
    "ut2004", // 156
    "vemmi", // 157
    "ventrilo", // 158
    "videotex", // 159
    "view-source", // 160
    "wais", // 161
    "webcal", // 162
    "ws", // 163
    "wss", // 164
    "wtai", // 165
    "wyciwyg", // 166
    "xcon", // 167
    "xcon-userid", // 168
    "xfire", // 169
    "xmlrpc.beep", // 170
    "xmlrpc.beeps", // 171
    "xmpp", // 172
    "xri", // 173
    "ymsgr", // 174
    "javascript", // 175
    "jdbc", // 176
    "doi", // 177
    "example1", // 178
    "example2", // 179
    "example3", // 180
    "example4", // 181
];

