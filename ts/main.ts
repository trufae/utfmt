import { convertStyle, formatWithTags } from './format.ts';

// Check if a file path is provided as command line argument
if (Deno.args.length > 0) {
  const filePath = Deno.args[0];
  try {
    const fileContent = await Deno.readTextFile(filePath);
    console.log(formatWithTags(fileContent));
  } catch (error) {
    console.error(`Error reading file ${filePath}:`, error.message);
  }
} else {
  // No file argument provided - use example code
  const input = `This is <bold>bold</bold> <underline>and</underline> <italic>italic</italic>.`;
  console.log(formatWithTags(input));
  console.log(convertStyle('Hello 123', 'bold'));
}
