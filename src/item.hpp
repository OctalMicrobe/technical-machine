// Item header
// Copyright (C) 2012 David Stone
//
// This file is part of Technical Machine.
//
// Technical Machine is free software: you can redistribute it and / or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

namespace technicalmachine {

class Item {
	public:
		enum Items {
			NO_ITEM, ADAMANT_ORB, AGUAV_BERRY, AIR_MAIL, AMULET_COIN,
			ANTIDOTE, APICOT_BERRY, ARMOR_FOSSIL, ASPEAR_BERRY, AWAKENING,
			BABIRI_BERRY, BELUE_BERRY, BERRY_JUICE, BICYCLE, BIG_MUSHROOM,
			BIG_PEARL, BIG_ROOT, BLACK_BELT, BLACK_FLUTE, BLACK_SLUDGE,
			BLACKGLASSES, BLOOM_MAIL, BLUE_FLUTE, BLUE_SCARF, BLUE_SHARD,
			BLUK_BERRY, BRICK_MAIL, BRIGHTPOWDER, BUBBLE_MAIL, BURN_HEAL,
			CALCIUM, CARBOS, CHARCOAL, CHARTI_BERRY, CHERI_BERRY,
			CHERISH_BALL, CHESTO_BERRY, CHILAN_BERRY, CHOICE_BAND, CHOICE_SCARF,
			CHOICE_SPECS, CHOPLE_BERRY, CLAW_FOSSIL, CLEANSE_TAG, COBA_BERRY,
			COIN_CASE, COLBUR_BERRY, CORNN_BERRY, COUPON_1, COUPON_2,
			COUPON_3, CUSTAP_BERRY, DAMP_MULCH, DAMP_ROCK, DAWN_STONE,
			DEEPSEASCALE, DEEPSEATOOTH, DESTINY_KNOT, DIRE_HIT, DIVE_BALL,
			DOME_FOSSIL, DRACO_PLATE, DRAGON_FANG, DRAGON_SCALE, DREAD_PLATE,
			DUBIOUS_DISC, DURIN_BERRY, DUSK_BALL, DUSK_STONE, EARTH_PLATE,
			ELECTIRIZER, ELIXIR, ENERGY_ROOT, ENERGYPOWDER, ENIGMA_BERRY,
			ESCAPE_ROPE, ETHER, EVERSTONE, EXP_SHARE, EXPERT_BELT,
			EXPLORER_KIT, FASHION_CASE, FIGY_BERRY, FIRE_STONE, FIST_PLATE,
			FLAME_MAIL, FLAME_ORB, FLAME_PLATE, FLUFFY_TAIL, FOCUS_BAND,
			FOCUS_SASH, FRESH_WATER, FULL_HEAL, FULL_INCENSE, FULL_RESTORE,
			GALACTIC_KEY, GANLON_BERRY, GOOD_ROD, GOOEY_MULCH, GRASS_MAIL,
			GREAT_BALL, GREEN_SCARF, GREEN_SHARD, GREPA_BERRY, GRIP_CLAW,
			GRISEOUS_ORB, GROWTH_MULCH, GUARD_SPEC, HABAN_BERRY, HARD_STONE,
			HEAL_BALL, HEAL_POWDER, HEART_MAIL, HEART_SCALE, HEAT_ROCK,
			HELIX_FOSSIL, HM01, HM02, HM03, HM04,
			HM05, HM06, HM07, HM08, HONDEW_BERRY,
			HONEY, HP_UP, HYPER_POTION, IAPAPA_BERRY, ICE_HEAL,
			ICICLE_PLATE, ICY_ROCK, INSECT_PLATE, IRON, IRON_BALL,
			IRON_PLATE, JABOCA_BERRY, JOURNAL, KASIB_BERRY, KEBIA_BERRY,
			KELPSY_BERRY, KINGS_ROCK, LAGGING_TAIL, LANSAT_BERRY, LAVA_COOKIE,
			LAX_INCENSE, LEAF_STONE, LEFTOVERS, LEMONADE, LEPPA_BERRY,
			LIECHI_BERRY, LIFE_ORB, LIGHT_BALL, LIGHT_CLAY, LOOT_SACK,
			LUCK_INCENSE, LUCKY_EGG, LUCKY_PUNCH, LUM_BERRY, LUNAR_WING,
			LUSTROUS_ORB, LUXURY_BALL, MACHO_BRACE, MAGMARIZER, MAGNET,
			MAGO_BERRY, MAGOST_BERRY, MASTER_BALL, MAX_ELIXIR, MAX_ETHER,
			MAX_POTION, MAX_REPEL, MAX_REVIVE, MEADOW_PLATE, MEMBER_CARD,
			MENTAL_HERB, METAL_COAT, METAL_POWDER, METRONOME, MICLE_BERRY,
			MIND_PLATE, MIRACLE_SEED, MOOMOO_MILK, MOON_STONE, MOSAIC_MAIL,
			MUSCLE_BAND, MYSTIC_WATER, NANAB_BERRY, NEST_BALL, NET_BALL,
			NEVERMELTICE, NOMEL_BERRY, NUGGET, OAKS_LETTER, OCCA_BERRY,
			ODD_INCENSE, ODD_KEYSTONE, OLD_AMBER, OLD_CHARM, OLD_GATEAU,
			OLD_ROD, ORAN_BERRY, OVAL_STONE, PAL_PAD, PAMTRE_BERRY,
			PARCEL, PARLYZ_HEAL, PASSHO_BERRY, PAYAPA_BERRY, PEARL,
			PECHA_BERRY, PERSIM_BERRY, PETAYA_BERRY, PINAP_BERRY, PINK_SCARF,
			POFFIN_CASE, POINT_CARD, POISON_BARB, POKE_BALL, POKE_DOLL,
			POKE_RADAR, POMEG_BERRY, POTION, POWER_ANKLET, POWER_BAND,
			POWER_BELT, POWER_BRACER, POWER_HERB, POWER_LENS, POWER_WEIGHT,
			PP_MAX, PP_UP, PREMIER_BALL, PROTECTOR, PROTEIN,
			PURE_INCENSE, QUALOT_BERRY, QUICK_BALL, QUICK_CLAW, QUICK_POWDER,
			RABUTA_BERRY, RARE_BONE, RARE_CANDY, RAWST_BERRY, RAZOR_CLAW,
			RAZOR_FANG, RAZZ_BERRY, REAPER_CLOTH, RED_FLUTE, RED_SCARF,
			RED_SHARD, REPEAT_BALL, REPEL, REVIVAL_HERB, REVIVE,
			RINDO_BERRY, ROCK_INCENSE, ROOT_FOSSIL, ROSE_INCENSE, ROWAP_BERRY,
			SACRED_ASH, SAFARI_BALL, SALAC_BERRY, SCOPE_LENS, SEA_INCENSE,
			SEAL_BAG, SEAL_CASE, SECRETPOTION, SHARP_BEAK, SHED_SHELL,
			SHELL_BELL, SHINY_STONE, SHOAL_SALT, SHOAL_SHELL, SHUCA_BERRY,
			SILK_SCARF, SILVERPOWDER, SITRUS_BERRY, SKULL_FOSSIL, SKY_PLATE,
			SMOKE_BALL, SMOOTH_ROCK, SNOW_MAIL, SODA_POP, SOFT_SAND,
			SOOTHE_BELL, SOUL_DEW, SPACE_MAIL, SPELL_TAG, SPELON_BERRY,
			SPLASH_PLATE, SPOOKY_PLATE, SPRAYDUCK, STABLE_MULCH, STAR_PIECE,
			STARDUST, STARF_BERRY, STEEL_MAIL, STICK, STICKY_BARB,
			STONE_PLATE, STORAGE_KEY, SUITE_KEY, SUN_STONE, SUPER_POTION,
			SUPER_REPEL, SUPER_ROD, TAMATO_BERRY, TANGA_BERRY, THICK_CLUB,
			THUNDERSTONE, TIMER_BALL, TINYMUSHROOM, TM01, TM02,
			TM03, TM04, TM05, TM06, TM07,
			TM08, TM09, TM10, TM11, TM12,
			TM13, TM14, TM15, TM16, TM17,
			TM18, TM19, TM20, TM21, TM22,
			TM23, TM24, TM25, TM26, TM27,
			TM28, TM29, TM30, TM31, TM32,
			TM33, TM34, TM35, TM36, TM37,
			TM38, TM39, TM40, TM41, TM42,
			TM43, TM44, TM45, TM46, TM47,
			TM48, TM49, TM50, TM51, TM52,
			TM53, TM54, TM55, TM56, TM57,
			TM58, TM59, TM60, TM61, TM62,
			TM63, TM64, TM65, TM66, TM67,
			TM68, TM69, TM70, TM71, TM72,
			TM73, TM74, TM75, TM76, TM77,
			TM78, TM79, TM80, TM81, TM82,
			TM83, TM84, TM85, TM86, TM87,
			TM88, TM89, TM90, TM91, TM92,
			TOWN_MAP, TOXIC_ORB, TOXIC_PLATE, TUNNEL_MAIL, TWISTEDSPOON,
			ULTRA_BALL, UP_GRADE, VS_SEEKER, WACAN_BERRY, WATER_STONE,
			WATMEL_BERRY, WAVE_INCENSE, WEPEAR_BERRY, WHITE_FLUTE, WHITE_HERB,
			WIDE_LENS, WIKI_BERRY, WISE_GLASSES, WORKS_KEY, X_ACCURACY,
			X_ATTACK, X_DEFEND, X_SP_DEF, X_SPECIAL, X_SPEED,
			YACHE_BERRY, YELLOW_FLUTE, YELLOW_SCARF, YELLOW_SHARD, ZAP_PLATE,
			ZINC, ZOOM_LENS, END
		};
	
		Items name;
	
		Item ();
		explicit Item (Items item);
		explicit Item (std::string const & str);
		bool is_set () const;
		bool is_choice_item () const;
		int get_berry_power () const;		// Returns 0 for non-berries
		int get_fling_power () const;
		bool blocks_trick () const;
		static std::string to_string (Items name);
		std::string to_string () const;
		static Items from_string (std::string const & str);
};

}	// namespace technicalmachine
#endif	// ITEM_HPP_
