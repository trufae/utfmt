# Unicode Text Formatter

A powerful TypeScript/Deno utility for formatting text using Unicode Mathematical Alphanumeric Symbols. Supports various typographic styles through XML-like tags or direct style conversion.

## Features

- **Multiple Unicode styles** - Bold, italic, script, double-struck, and more
- **XML-like tag syntax** - Easy formatting with familiar `<style>text</style>` syntax
- **Direct style conversion** - Apply styles programmatically to plain text
- **Deno runtime** - Modern, secure JavaScript/TypeScript execution

**Note:** The formatter currently does not support nested tags within the same formatting context.

## Supported Typographies

All 17 Unicode styles available:

1. **bold** → 𝐀𝐛𝐜𝟏𝟐𝟑
2. **italic** → 𝐴𝑏𝑐
3. **script** → 𝒜𝒷𝒸
4. **doublestruck** → 𝔸𝕓𝕔𝟙𝟚𝟛
5. **underline** → A̲b̲c̲1̲2̲3̲
6. **strikethrough** → A̶b̶c̶1̶2̶3̶
7. **fraktur** → 𝔄𝔟𝔠
8. **bolditalic** → 𝑨𝒃𝒄
9. **sansserif** → 𝖠𝖻𝖼𝟣𝟤𝟥
10. **sansserifitalic** → 𝘈𝘣𝘤
11. **monospace** → 𝙰𝚋𝚌𝟷𝟸𝟹
12. **boldscript** → 𝓐𝓫𝓬
13. **boldfraktur** → 𝖆𝖇𝖈
14. **sansseribbold** → 𝖠𝖻𝖼𝟣𝟤𝟥
15. **sansserifbolditalic** → 𝘼𝙗𝙘
16. **openface** → 𝔸𝕓𝕔
17. **smallcaps** → ᴀʙᴄ

## Usage

### Command Line

```bash
# Format a file
deno run --allow-read main.ts input.txt

# Or using Makefile
make
```

### Programmatic API

```typescript
import { convertStyle, formatWithTags } from './format.ts';

// Format text with tags
const formatted = formatWithTags('Hello <bold>World</bold>!');
console.log(formatted); // Hello 𝐖𝐨𝐫𝐥𝐝!

// Direct style conversion
const boldText = convertStyle('Hello 123', 'bold');
console.log(boldText); // 𝐇𝐞𝐥𝐥𝐨 𝟏𝟐𝟑

// Note: Nested tags are not supported
// formatWithTags('<monospace>Text with <bold>bold</bold> inside</monospace>')
// would not process the inner bold tag
```

## Examples

The `text.utfmt` file contains examples demonstrating all supported styles:

```xml
<bold>Mathematical Bold</bold>
<italic>Mathematical Italic</italic>
<script>Mathematical Script</script>
<doublestruck>Double-struck</doublestruck>
<underline>Emphasis</underline>
<strikethrough>Corrections</strikethrough>
<fraktur>Gothic Calligraphy</fraktur>
<bolditalic>Bold Italic</bolditalic>
<sansserif>Clean Sans-serif</sansserif>
<sansserifitalic>Sans-serif Italic</sansserifitalic>
<monospace>Code Examples</monospace>
<boldscript>Bold Script</boldscript>
<boldfraktur>Bold Gothic</boldfraktur>
<sansseribbold>Sans-serif Bold</sansseribbold>
<sansserifbolditalic>Sans-serif Bold Italic</sansserifbolditalic>
<openface>Open Type</openface>
<smallcaps>Stylized Text</smallcaps>
```

Run the formatter to see all styles in action:

```bash
deno run --allow-read main.ts text.utfmt
```

## Requirements

- Deno runtime (https://deno.land/)
- Modern terminal/editor with Unicode support

## License

[MIT License](LICENSE)
