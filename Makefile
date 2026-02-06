all:
	deno run --allow-read main.ts text.utfmt

test:
	echo "Testing Unicode Formatter..."
	deno run --allow-read main.ts text.utfmt
