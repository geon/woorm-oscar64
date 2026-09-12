#include "../../src/level.h"


char level_title_screen_title[] = "Title";

uint8_t level_title_screen_chars[] = {
#embed lzo "title_screen_chars.bin"
};
uint8_t level_title_screen_colors[] = {
#embed lzo "title_screen_colors.bin"
};
uint8_t level_title_screen_charset[] = {
#embed lzo "title_screen_charset.bin"
};

const Level level_title_screen = {
	level_title_screen_title,
	1,
	9,
	{
		{{15, 13}, 0},
		{{19, 11}, 0},
		{{-3, -6}, 2},
		{{-3, -6}, 3},
	},
	level_title_screen_chars,
	level_title_screen_colors,
	level_title_screen_charset,
};


char level_love_title[] = "Title";

uint8_t level_love_chars[] = {
#embed lzo "love_chars.bin"
};
uint8_t level_love_colors[] = {
#embed lzo "love_colors.bin"
};
uint8_t level_love_charset[] = {
#embed lzo "love_charset.bin"
};

const Level level_love = {
	level_love_title,
	1,
	2,
	{
		{{12, 17}, 0},
		{{28, 17}, 0},
		{{9, 8}, 2},
		{{28, 8}, 2},
	},
	level_love_chars,
	level_love_colors,
	level_love_charset,
};


char level_hate_title[] = "Title";

uint8_t level_hate_chars[] = {
#embed lzo "hate_chars.bin"
};
uint8_t level_hate_colors[] = {
#embed lzo "hate_colors.bin"
};
uint8_t level_hate_charset[] = {
#embed lzo "hate_charset.bin"
};

const Level level_hate = {
	level_hate_title,
	15,
	9,
	{
		{{8, 12}, 0},
		{{19, 4}, 1},
		{{31, 12}, 2},
		{{20, 20}, 3},
	},
	level_hate_chars,
	level_hate_colors,
	level_hate_charset,
};


char level_pain_title[] = "Title";

uint8_t level_pain_chars[] = {
#embed lzo "pain_chars.bin"
};
uint8_t level_pain_colors[] = {
#embed lzo "pain_colors.bin"
};
uint8_t level_pain_charset[] = {
#embed lzo "pain_charset.bin"
};

const Level level_pain = {
	level_pain_title,
	1,
	2,
	{
		{{14, 19}, 0},
		{{30, 19}, 0},
		{{14, 5}, 2},
		{{25, 5}, 2},
	},
	level_pain_chars,
	level_pain_colors,
	level_pain_charset,
};


char level_geon_title[] = "Title";

uint8_t level_geon_chars[] = {
#embed lzo "geon_chars.bin"
};
uint8_t level_geon_colors[] = {
#embed lzo "geon_colors.bin"
};
uint8_t level_geon_charset[] = {
#embed lzo "geon_charset.bin"
};

const Level level_geon = {
	level_geon_title,
	1,
	9,
	{
		{{10, 9}, 0},
		{{28, 9}, 0},
		{{1, 9}, 0},
		{{37, 9}, 0},
	},
	level_geon_chars,
	level_geon_colors,
	level_geon_charset,
};


char level_foresight_title[] = "Title";

uint8_t level_foresight_chars[] = {
#embed lzo "foresight_chars.bin"
};
uint8_t level_foresight_colors[] = {
#embed lzo "foresight_colors.bin"
};
uint8_t level_foresight_charset[] = {
#embed lzo "foresight_charset.bin"
};

const Level level_foresight = {
	level_foresight_title,
	8,
	9,
	{
		{{19, 17}, 0},
		{{21, 17}, 0},
		{{19, 7}, 2},
		{{21, 7}, 2},
	},
	level_foresight_chars,
	level_foresight_colors,
	level_foresight_charset,
};


char level_polka_title[] = "Title";

uint8_t level_polka_chars[] = {
#embed lzo "polka_chars.bin"
};
uint8_t level_polka_colors[] = {
#embed lzo "polka_colors.bin"
};
uint8_t level_polka_charset[] = {
#embed lzo "polka_charset.bin"
};

const Level level_polka = {
	level_polka_title,
	1,
	2,
	{
		{{13, 16}, 0},
		{{25, 16}, 0},
		{{13, 8}, 2},
		{{25, 8}, 2},
	},
	level_polka_chars,
	level_polka_colors,
	level_polka_charset,
};


char level_bub_01_title[] = "Title";

uint8_t level_bub_01_chars[] = {
#embed lzo "bub_01_chars.bin"
};
uint8_t level_bub_01_colors[] = {
#embed lzo "bub_01_colors.bin"
};
uint8_t level_bub_01_charset[] = {
#embed lzo "bub_01_charset.bin"
};

const Level level_bub_01 = {
	level_bub_01_title,
	1,
	2,
	{
		{{11, 23}, 1},
		{{29, 23}, 3},
		{{14, 8}, 1},
		{{12, 6}, 2},
	},
	level_bub_01_chars,
	level_bub_01_colors,
	level_bub_01_charset,
};


char level_corrupt_title[] = "Title";

uint8_t level_corrupt_chars[] = {
#embed lzo "corrupt_chars.bin"
};
uint8_t level_corrupt_colors[] = {
#embed lzo "corrupt_colors.bin"
};
uint8_t level_corrupt_charset[] = {
#embed lzo "corrupt_charset.bin"
};

const Level level_corrupt = {
	level_corrupt_title,
	8,
	9,
	{
		{{12, 13}, 1},
		{{27, 13}, 3},
		{{14, 1}, 3},
		{{25, 1}, 1},
	},
	level_corrupt_chars,
	level_corrupt_colors,
	level_corrupt_charset,
};


char level_mr_man_title[] = "Title";

uint8_t level_mr_man_chars[] = {
#embed lzo "mr_man_chars.bin"
};
uint8_t level_mr_man_colors[] = {
#embed lzo "mr_man_colors.bin"
};
uint8_t level_mr_man_charset[] = {
#embed lzo "mr_man_charset.bin"
};

const Level level_mr_man = {
	level_mr_man_title,
	1,
	9,
	{
		{{16, 9}, 0},
		{{21, 4}, 1},
		{{22, 12}, 2},
		{{16, 16}, 3},
	},
	level_mr_man_chars,
	level_mr_man_colors,
	level_mr_man_charset,
};


char level_ocd_title[] = "Title";

uint8_t level_ocd_chars[] = {
#embed lzo "ocd_chars.bin"
};
uint8_t level_ocd_colors[] = {
#embed lzo "ocd_colors.bin"
};
uint8_t level_ocd_charset[] = {
#embed lzo "ocd_charset.bin"
};

const Level level_ocd = {
	level_ocd_title,
	1,
	6,
	{
		{{19, 7}, 0},
		{{20, 7}, 0},
		{{19, 16}, 2},
		{{20, 16}, 2},
	},
	level_ocd_chars,
	level_ocd_colors,
	level_ocd_charset,
};


char level_square_off_title[] = "Title";

uint8_t level_square_off_chars[] = {
#embed lzo "square_off_chars.bin"
};
uint8_t level_square_off_colors[] = {
#embed lzo "square_off_colors.bin"
};
uint8_t level_square_off_charset[] = {
#embed lzo "square_off_charset.bin"
};

const Level level_square_off = {
	level_square_off_title,
	1,
	2,
	{
		{{22, 19}, 0},
		{{10, 12}, 1},
		{{17, 5}, 2},
		{{29, 7}, 3},
	},
	level_square_off_chars,
	level_square_off_colors,
	level_square_off_charset,
};


char level_geon_2_title[] = "Title";

uint8_t level_geon_2_chars[] = {
#embed lzo "geon_2_chars.bin"
};
uint8_t level_geon_2_colors[] = {
#embed lzo "geon_2_colors.bin"
};
uint8_t level_geon_2_charset[] = {
#embed lzo "geon_2_charset.bin"
};

const Level level_geon_2 = {
	level_geon_2_title,
	1,
	9,
	{
		{{13, 19}, 0},
		{{28, 19}, 0},
		{{35, 7}, 2},
		{{3, 7}, 2},
	},
	level_geon_2_chars,
	level_geon_2_colors,
	level_geon_2_charset,
};


char level_quatro_title[] = "Title";

uint8_t level_quatro_chars[] = {
#embed lzo "quatro_chars.bin"
};
uint8_t level_quatro_colors[] = {
#embed lzo "quatro_colors.bin"
};
uint8_t level_quatro_charset[] = {
#embed lzo "quatro_charset.bin"
};

const Level level_quatro = {
	level_quatro_title,
	1,
	9,
	{
		{{8, 14}, 0},
		{{11, 15}, 0},
		{{33, 13}, 2},
		{{27, 8}, 3},
	},
	level_quatro_chars,
	level_quatro_colors,
	level_quatro_charset,
};


char level_wory_title[] = "Title";

uint8_t level_wory_chars[] = {
#embed lzo "wory_chars.bin"
};
uint8_t level_wory_colors[] = {
#embed lzo "wory_colors.bin"
};
uint8_t level_wory_charset[] = {
#embed lzo "wory_charset.bin"
};

const Level level_wory = {
	level_wory_title,
	1,
	9,
	{
		{{32, 17}, 3},
		{{7, 17}, 1},
		{{8, 6}, 2},
		{{31, 6}, 2},
	},
	level_wory_chars,
	level_wory_colors,
	level_wory_charset,
};


char level_load_title[] = "Title";

uint8_t level_load_chars[] = {
#embed lzo "load_chars.bin"
};
uint8_t level_load_colors[] = {
#embed lzo "load_colors.bin"
};
uint8_t level_load_charset[] = {
#embed lzo "load_charset.bin"
};

const Level level_load = {
	level_load_title,
	1,
	6,
	{
		{{5, 17}, 0},
		{{34, 17}, 0},
		{{7, 4}, 3},
		{{31, 6}, 1},
	},
	level_load_chars,
	level_load_colors,
	level_load_charset,
};


char level_ms_man_title[] = "Title";

uint8_t level_ms_man_chars[] = {
#embed lzo "ms_man_chars.bin"
};
uint8_t level_ms_man_colors[] = {
#embed lzo "ms_man_colors.bin"
};
uint8_t level_ms_man_charset[] = {
#embed lzo "ms_man_charset.bin"
};

const Level level_ms_man = {
	level_ms_man_title,
	1,
	9,
	{
		{{12, 5}, 0},
		{{22, 3}, 1},
		{{26, 12}, 2},
		{{15, 16}, 3},
	},
	level_ms_man_chars,
	level_ms_man_colors,
	level_ms_man_charset,
};


char level_bub_29_title[] = "Title";

uint8_t level_bub_29_chars[] = {
#embed lzo "bub_29_chars.bin"
};
uint8_t level_bub_29_colors[] = {
#embed lzo "bub_29_colors.bin"
};
uint8_t level_bub_29_charset[] = {
#embed lzo "bub_29_charset.bin"
};

const Level level_bub_29 = {
	level_bub_29_title,
	14,
	6,
	{
		{{10, 21}, 1},
		{{30, 23}, 3},
		{{12, 14}, 2},
		{{25, 12}, 3},
	},
	level_bub_29_chars,
	level_bub_29_colors,
	level_bub_29_charset,
};


char level_fair_n_square_title[] = "Title";

uint8_t level_fair_n_square_chars[] = {
#embed lzo "fair_n_square_chars.bin"
};
uint8_t level_fair_n_square_colors[] = {
#embed lzo "fair_n_square_colors.bin"
};
uint8_t level_fair_n_square_charset[] = {
#embed lzo "fair_n_square_charset.bin"
};

const Level level_fair_n_square = {
	level_fair_n_square_title,
	1,
	2,
	{
		{{20, 17}, 0},
		{{19, 7}, 2},
		{{26, 8}, 2},
		{{13, 16}, 0},
	},
	level_fair_n_square_chars,
	level_fair_n_square_colors,
	level_fair_n_square_charset,
};


char level_sus_title[] = "Title";

uint8_t level_sus_chars[] = {
#embed lzo "sus_chars.bin"
};
uint8_t level_sus_colors[] = {
#embed lzo "sus_colors.bin"
};
uint8_t level_sus_charset[] = {
#embed lzo "sus_charset.bin"
};

const Level level_sus = {
	level_sus_title,
	1,
	9,
	{
		{{19, 19}, 0},
		{{10, 16}, 1},
		{{17, 5}, 2},
		{{30, 11}, 3},
	},
	level_sus_chars,
	level_sus_colors,
	level_sus_charset,
};


const Level *levels[]  = {
	&level_love,
	&level_hate,
	&level_pain,
	&level_geon,
	&level_foresight,
	&level_polka,
	&level_bub_01,
	&level_corrupt,
	&level_mr_man,
	&level_ocd,
	&level_square_off,
	&level_geon_2,
	&level_quatro,
	&level_wory,
	&level_load,
	&level_ms_man,
	&level_bub_29,
	&level_fair_n_square,
	&level_sus
};
