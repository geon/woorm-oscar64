import { importLevels } from "./import-levels.js";
import { importWormCharset } from "./import-worm-charset.js";

function main() {
	const charsetStaticSize = importWormCharset();
	importLevels(charsetStaticSize);
}

main();
