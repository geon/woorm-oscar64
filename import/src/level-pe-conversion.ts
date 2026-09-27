import type { Level, PlayerStart } from "./Level.js";
import type { PeFileData } from "./pe/pe-file.js";

export function peFileDataToLevels(peFileData: PeFileData): Level[] {
	return peFileData.screens.map((screen) => {
		if (!screen) {
			throw new Error("Missing screen.");
		}

		const charset = peFileData.charsets[screen.characterSet];
		if (!charset) {
			throw new Error("Missing charset.");
		}

		if (screen.sprites.length !== 4) {
			throw new Error(
				`Wrong number of sprites. Should be 4, is ${screen.sprites.length}.`,
			);
		}

		const playerStarts = screen.sprites.map(
			(sprite): PlayerStart => ({
				position: {
					// https://www.lemon64.com/forum/viewtopic.php?t=73528
					//  x=24 y=50 will put a sprite in the top left corner of the display, touching the border.
					x: Math.round((sprite.x - 24) / 8),
					y: Math.round((sprite.y - 50) / 8),
				},
				direction:
					//
					peFileData.spriteSets[sprite.setId]?.sprites
						.map((x) => x.uid)
						.indexOf(sprite.uid) ?? 0,
			}),
		);

		return {
			name: screen.name,
			multiColor1: screen.multiColor1,
			multiColor2: screen.multiColor2,
			playerStarts,
			chars: screen.charData.flat(),
			colors: screen.colorData.flat(),
			charset: charset.bitmaps,
		};
	});
}
