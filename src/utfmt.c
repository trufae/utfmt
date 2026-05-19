#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	BOLD, ITALIC, SCRIPT, DOUBLESTRUCK, UNDERLINE, STRIKE, FRAKTUR,
	BOLDITALIC, SANSSERIF, SANSSERIFITALIC, MONOSPACE, BOLDSCRIPT,
	BOLDFRAKTUR, SANSSERIBBOLD, SANSSERIFBOLDITALIC, OPENFACE, SMALLCAPS
};

static const char *styles[] = {
	"bold", "italic", "script", "doublestruck", "underline", "strikethrough",
	"fraktur", "bolditalic", "sansserif", "sansserifitalic", "monospace",
	"boldscript", "boldfraktur", "sansseribbold", "sansserifbolditalic",
	"openface", "smallcaps"
};

static int style_id(const char *s, size_t n) {
	for (int i = 0; i < (int)(sizeof(styles) / sizeof(*styles)); i++)
		if (strlen(styles[i]) == n && !memcmp(styles[i], s, n)) return i;
	if (n == 13 && !memcmp(s, "sansserifbold", n)) return SANSSERIBBOLD;
	return -1;
}

static int eqci(const char *a, const char *b, size_t n) {
	while (n--) if (tolower((unsigned char)*a++) != tolower((unsigned char)*b++)) return 0;
	return 1;
}

static void putu(FILE *out, unsigned cp) {
	if (cp < 0x80) fputc(cp, out);
	else if (cp < 0x800) { fputc(0xC0 | (cp >> 6), out); fputc(0x80 | (cp & 0x3F), out); }
	else if (cp < 0x10000) {
		fputc(0xE0 | (cp >> 12), out); fputc(0x80 | ((cp >> 6) & 0x3F), out); fputc(0x80 | (cp & 0x3F), out);
	} else {
		fputc(0xF0 | (cp >> 18), out); fputc(0x80 | ((cp >> 12) & 0x3F), out);
		fputc(0x80 | ((cp >> 6) & 0x3F), out); fputc(0x80 | (cp & 0x3F), out);
	}
}

static unsigned ex(unsigned base, int i, const int *idx, const unsigned *val, int n) {
	for (int j = 0; j < n; j++) if (idx[j] == i) return val[j];
	return base + i;
}

static unsigned mapcp(char c, int st, unsigned *comb) {
	int i;
	*comb = 0;
	if (st == UNDERLINE || st == STRIKE) {
		if (isalnum((unsigned char)c)) *comb = st == UNDERLINE ? 0x332 : 0x335;
		return (unsigned char)c;
	}
	if (c >= 'A' && c <= 'Z') {
		static const int se[] = {1,4,5,7,8,11,12,17}, de[] = {2,7,13,15,16,17,25};
		static const int fe[] = {2,7,8,17,25};
		static const unsigned sv[] = {0x212C,0x2130,0x2131,0x210B,0x2110,0x2112,0x2133,0x211B};
		static const unsigned dv[] = {0x2102,0x210D,0x2115,0x2119,0x211A,0x211D,0x2124};
		static const unsigned fv[] = {0x212D,0x210C,0x2111,0x211C,0x2128};
		i = c - 'A';
		switch (st) {
		case BOLD: return 0x1D400 + i;
		case ITALIC: return 0x1D434 + i;
		case BOLDITALIC: return 0x1D468 + i;
		case SCRIPT: return ex(0x1D49C, i, se, sv, 8);
		case DOUBLESTRUCK: case OPENFACE: return ex(0x1D538, i, de, dv, 7);
		case FRAKTUR: return ex(0x1D504, i, fe, fv, 5);
		case SANSSERIF: return 0x1D5A0 + i;
		case SANSSERIBBOLD: return 0x1D5D4 + i;
		case SANSSERIFITALIC: return 0x1D608 + i;
		case MONOSPACE: return 0x1D670 + i;
		case BOLDSCRIPT: return 0x1D4D0 + i;
		case BOLDFRAKTUR: return 0x1D56C + i;
		case SANSSERIFBOLDITALIC: return 0x1D63C + i;
		case SMALLCAPS: return c;
		}
	}
	if (c >= 'a' && c <= 'z') {
		static const int il[] = {7};
		static const int sl[] = {4,6,14};
		static const unsigned iv[] = {0x210E};
		static const unsigned sv[] = {0x212F,0x210A,0x2134};
		static const unsigned sc[] = {
			0x1D00,0x299,0x1D04,0x1D05,0x1D07,0x493,0x262,0x29C,0x26A,0x1D0A,
			0x1D0B,0x29F,0x1D0D,0x274,0x1D0F,0x1D18,0x1EB,0x280,0x73,0x1D1B,
			0x1D1C,0x1D20,0x1D21,0x78,0x28F,0x1D22
		};
		i = c - 'a';
		switch (st) {
		case BOLD: return 0x1D41A + i;
		case ITALIC: return ex(0x1D44E, i, il, iv, 1);
		case BOLDITALIC: return 0x1D482 + i;
		case SCRIPT: return ex(0x1D4B6, i, sl, sv, 3);
		case DOUBLESTRUCK: case OPENFACE: return 0x1D552 + i;
		case FRAKTUR: return 0x1D51E + i;
		case SANSSERIF: return 0x1D5BA + i;
		case SANSSERIBBOLD: return 0x1D5EE + i;
		case SANSSERIFITALIC: return 0x1D622 + i;
		case MONOSPACE: return 0x1D68A + i;
		case BOLDSCRIPT: return 0x1D4EA + i;
		case BOLDFRAKTUR: return 0x1D586 + i;
		case SANSSERIFBOLDITALIC: return 0x1D656 + i;
		case SMALLCAPS: return sc[i];
		}
	}
	if (c >= '0' && c <= '9') {
		i = c - '0';
		switch (st) {
		case BOLD: return 0x1D7CE + i;
		case DOUBLESTRUCK: return 0x1D7D8 + i;
		case SANSSERIF: return 0x1D7E2 + i;
		case SANSSERIBBOLD: return 0x1D7EC + i;
		case MONOSPACE: return 0x1D7F6 + i;
		}
	}
	return (unsigned char)c;
}

static void convert(const char *s, size_t n, int st, FILE *out) {
	while (n--) {
		unsigned comb, cp = mapcp(*s++, st, &comb);
		putu(out, cp);
		if (comb) putu(out, comb);
	}
}

static const char *closing(const char *s, const char *tag, size_t n) {
	for (; *s; s++) if (s[0] == '<' && s[1] == '/' && eqci(s + 2, tag, n) && s[n + 2] == '>') return s;
	return NULL;
}

static void format(const char *s, FILE *out) {
	while (*s) {
		if (*s == '<' && isalpha((unsigned char)s[1])) {
			const char *q = s + 1;
			while (isalpha((unsigned char)*q)) q++;
			if (*q == '>') {
				const char *body = q + 1, *end = closing(body, s + 1, (size_t)(q - s - 1));
				if (end) {
					int st = style_id(s + 1, (size_t)(q - s - 1));
					if (st < 0) fwrite(body, 1, (size_t)(end - body), out);
					else convert(body, (size_t)(end - body), st, out);
					s = end + (q - s - 1) + 3;
					continue;
				}
			}
		}
		fputc(*s++, out);
	}
}

static char *readfile(const char *path) {
	FILE *f = fopen(path, "rb");
	long n;
	char *s;
	if (!f) return NULL;
	if (fseek(f, 0, SEEK_END) || (n = ftell(f)) < 0 || fseek(f, 0, SEEK_SET)) { fclose(f); return NULL; }
	s = malloc((size_t)n + 1);
	if (!s) { fclose(f); return NULL; }
	s[fread(s, 1, (size_t)n, f)] = 0;
	fclose(f);
	return s;
}

int main(int argc, char **argv) {
	if (argc > 1) {
		char *s = readfile(argv[1]);
		if (!s) { fprintf(stderr, "Error reading file %s\n", argv[1]); return 1; }
		format(s, stdout); putchar('\n'); free(s);
	} else {
		format("This is <bold>bold</bold> <underline>and</underline> <italic>italic</italic>.", stdout); putchar('\n');
		convert("Hello 123", 9, BOLD, stdout); putchar('\n');
	}
	return 0;
}
