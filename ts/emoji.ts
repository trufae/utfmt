// emoji.ts
// A simple emoji formatter using <:emoji_name:> syntax

/**
 * Common emoji mappings for basic formatting
 */
const emojiMappings = {
  // Facial expressions
  smile: '😊',
  grin: '😁',
  laugh: '😂',
  wink: '😉',
  hearteyes: '😍',
  cheeky: '😏',
  blush: '😊',
  innocent: '😇',
  angel: '😇',
  devil: '😈',
  angry: '😠',
  rage: '😡',
  cry: '😢',
  sob: '😭',
  sweat: '😅',
  confused: '😕',
  worried: '😟',
  tired: '😫',
  sleepy: '😴',
  sick: '🤢',
  vomit: '🤮',
  wow: '😲',
  starstruck: '🤩',
  party: '🥳',
  cool: '😎',
  sunglasses: '😎',

  // Objects and symbols
  heart: '❤️',
  star: '⭐',
  fire: '🔥',
  rocket: '🚀',
  thumbsup: '👍',
  thumbsdown: '👎',
  clap: '👏',
  check: '✅',
  x: '❌',
  warning: '⚠️',
  question: '❓',
  exclamation: '❗',
  flag: '🏁',
  trophy: '🏆',
  crown: '👑',
  money: '💰',
  gift: '🎁',
  balloon: '🎈',

  // Hands
  wave: '👋',
  pray: '🙏',
  pointright: '👉',
  pointleft: '👈',
  pointup: '👆',
  pointdown: '👇',

  // Animals
  cat: '🐱',
  dog: '🐶',
  panda: '🐼',
  bear: '🐻',
  monkey: '🐵',
  lion: '🦁',
  tiger: '🐯',
  rabbit: '🐰',
  fox: '🦊',
  wolf: '🐺',
  pig: '🐷',
  cow: '🐮',
  chicken: '🐔',
  penguin: '🐧',
  owl: '🦉',
  eagle: '🦅',

  // Food
  pizza: '🍕',
  burger: '🍔',
  fries: '🍟',
  sushi: '🍣',
  ramen: '🍜',
  coffee: '☕',
  beer: '🍺',
  wine: '🍷',
  cake: '🎂',
  icecream: '🍦',
  donut: '🍩',
  cookie: '🍪',

  // Nature
  sun: '☀️',
  moon: '🌙',
  star2: '🌟',
  cloud: '☁️',
  rainbow: '🌈',
  flower: '🌹',
  tree: '🌳',
  leaf: '🍃',

  // Miscellaneous
  clock: '⏰',
  phone: '📱',
  computer: '💻',
  book: '📖',
  pencil: '✏️',
  scissor: '✂️',
  lock: '🔒',
  key: '🔑',
  lightbulb: '💡',
  bomb: '💣',

} as const;

type EmojiKey = keyof typeof emojiMappings;

/**
 * Format text by replacing <:emoji_name:> patterns with actual emojis
 */
export function formatEmoji(input: string): string {
  return input.replace(
    /<:([a-zA-Z]+):>/g,
    (_, emojiName: string) => {
      const emojiKey = emojiName.toLowerCase() as EmojiKey;
      return emojiMappings[emojiKey] || `<:${emojiName}:>`;
    }
  );
}

/**
 * Get a specific emoji by name
 */
export function getEmoji(name: EmojiKey): string {
  return emojiMappings[name] || '';
}

/**
 * Get all available emoji names
 */
export function getAvailableEmojis(): string[] {
  return Object.keys(emojiMappings);
}