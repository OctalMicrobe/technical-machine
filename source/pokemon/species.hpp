// Species enum
// Copyright (C) 2014 David Stone
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

#ifndef POKEMON__SPECIES_HPP_
#define POKEMON__SPECIES_HPP_

#include "species_forward.hpp"
#include "../hash.hpp"

#include <cstdint>

namespace technicalmachine {

// Hyphens and spaces were replaced by underscores. Dots and apostrophes were
// removed.
//
// The following are my formats for species:
//
// Deoxys-Attack, Deoxys-Defense, Deoxys-Mediocre, Deoxys-Speed. All of these
// are standard except Deoxys-Mediocre, which is usually refered as simply
// Deoxys.
//
// Giratina-Altered, Giratina-Origin. Both of these are somewhat standard.
// Giratina-Altered is sometimes refered to as simply Giratina.
//
// The weaker Rotom form is Rotom. The appliance Rotom are Rotom-Mow,
// Rotom-Fan, Rotom-Frost, Rotom-Heat, Rotom-Wash.
//
// Shaymin-Land, Shaymin-Sky.

// Wormadam-Plant = Grass-type, Wormadam-Sandy = Ground-type,
// Wormadam-Trash = Steel-type. These names are based on the in-game Pokedex
// descriptions of the forms.

enum class Species : uint16_t {
	// Generation 1
	Bulbasaur,
	Ivysaur,
	Venusaur,
	Charmander,
	Charmeleon,
	Charizard,
	Squirtle,
	Wartortle,
	Blastoise,
	Caterpie,
	Metapod,
	Butterfree,
	Weedle,
	Kakuna,
	Beedrill,
	Pidgey,
	Pidgeotto,
	Pidgeot,
	Rattata,
	Raticate,
	Spearow,
	Fearow,
	Ekans,
	Arbok,
	Pikachu,
	Raichu,
	Sandshrew,
	Sandslash,
	Nidoran_F,
	Nidorina,
	Nidoqueen,
	Nidoran_M,
	Nidorino,
	Nidoking,
	Clefairy,
	Clefable,
	Vulpix,
	Ninetales,
	Jigglypuff,
	Wigglytuff,
	Zubat,
	Golbat,
	Oddish,
	Gloom,
	Vileplume,
	Paras,
	Parasect,
	Venonat,
	Venomoth,
	Diglett,
	Dugtrio,
	Meowth,
	Persian,
	Psyduck,
	Golduck,
	Mankey,
	Primeape,
	Growlithe,
	Arcanine,
	Poliwag,
	Poliwhirl,
	Poliwrath,
	Abra,
	Kadabra,
	Alakazam,
	Machop,
	Machoke,
	Machamp,
	Bellsprout,
	Weepinbell,
	Victreebel,
	Tentacool,
	Tentacruel,
	Geodude,
	Graveler,
	Golem,
	Ponyta,
	Rapidash,
	Slowpoke,
	Slowbro,
	Magnemite,
	Magneton,
	Farfetchd,
	Doduo,
	Dodrio,
	Seel,
	Dewgong,
	Grimer,
	Muk,
	Shellder,
	Cloyster,
	Gastly,
	Haunter,
	Gengar,
	Onix,
	Drowzee,
	Hypno,
	Krabby,
	Kingler,
	Voltorb,
	Electrode,
	Exeggcute,
	Exeggutor,
	Cubone,
	Marowak,
	Hitmonlee,
	Hitmonchan,
	Lickitung,
	Koffing,
	Weezing,
	Rhyhorn,
	Rhydon,
	Chansey,
	Tangela,
	Kangaskhan,
	Horsea,
	Seadra,
	Goldeen,
	Seaking,
	Staryu,
	Starmie,
	Mr_Mime,
	Scyther,
	Jynx,
	Electabuzz,
	Magmar,
	Pinsir,
	Tauros,
	Magikarp,
	Gyarados,
	Lapras,
	Ditto,
	Eevee,
	Vaporeon,
	Jolteon,
	Flareon,
	Porygon,
	Omanyte,
	Omastar,
	Kabuto,
	Kabutops,
	Aerodactyl,
	Snorlax,
	Articuno,
	Zapdos,
	Moltres,
	Dratini,
	Dragonair,
	Dragonite,
	Mewtwo,
	Mew,
	Generation_1_End,

	// Generation 2
	Chikorita = Generation_1_End,
	Bayleef,
	Meganium,
	Cyndaquil,
	Quilava,
	Typhlosion,
	Totodile,
	Croconaw,
	Feraligatr,
	Sentret,
	Furret,
	Hoothoot,
	Noctowl,
	Ledyba,
	Ledian,
	Spinarak,
	Ariados,
	Crobat,
	Chinchou,
	Lanturn,
	Pichu,
	Cleffa,
	Igglybuff,
	Togepi,
	Togetic,
	Natu,
	Xatu,
	Mareep,
	Flaaffy,
	Ampharos,
	Bellossom,
	Marill,
	Azumarill,
	Sudowoodo,
	Politoed,
	Hoppip,
	Skiploom,
	Jumpluff,
	Aipom,
	Sunkern,
	Sunflora,
	Yanma,
	Wooper,
	Quagsire,
	Espeon,
	Umbreon,
	Murkrow,
	Slowking,
	Misdreavus,
	Unown,
	Wobbuffet,
	Girafarig,
	Pineco,
	Forretress,
	Dunsparce,
	Gligar,
	Steelix,
	Snubbull,
	Granbull,
	Qwilfish,
	Scizor,
	Shuckle,
	Heracross,
	Sneasel,
	Teddiursa,
	Ursaring,
	Slugma,
	Magcargo,
	Swinub,
	Piloswine,
	Corsola,
	Remoraid,
	Octillery,
	Delibird,
	Mantine,
	Skarmory,
	Houndour,
	Houndoom,
	Kingdra,
	Phanpy,
	Donphan,
	Porygon2,
	Stantler,
	Smeargle,
	Tyrogue,
	Hitmontop,
	Smoochum,
	Elekid,
	Magby,
	Miltank,
	Blissey,
	Raikou,
	Entei,
	Suicune,
	Larvitar,
	Pupitar,
	Tyranitar,
	Lugia,
	Ho_Oh,
	Celebi,
	Generation_2_End,

	// Generation 3
	Treecko = Generation_2_End,
	Grovyle,
	Sceptile,
	Torchic,
	Combusken,
	Blaziken,
	Mudkip,
	Marshtomp,
	Swampert,
	Poochyena,
	Mightyena,
	Zigzagoon,
	Linoone,
	Wurmple,
	Silcoon,
	Beautifly,
	Cascoon,
	Dustox,
	Lotad,
	Lombre,
	Ludicolo,
	Seedot,
	Nuzleaf,
	Shiftry,
	Taillow,
	Swellow,
	Wingull,
	Pelipper,
	Ralts,
	Kirlia,
	Gardevoir,
	Surskit,
	Masquerain,
	Shroomish,
	Breloom,
	Slakoth,
	Vigoroth,
	Slaking,
	Nincada,
	Ninjask,
	Shedinja,
	Whismur,
	Loudred,
	Exploud,
	Makuhita,
	Hariyama,
	Azurill,
	Nosepass,
	Skitty,
	Delcatty,
	Sableye,
	Mawile,
	Aron,
	Lairon,
	Aggron,
	Meditite,
	Medicham,
	Electrike,
	Manectric,
	Plusle,
	Minun,
	Volbeat,
	Illumise,
	Roselia,
	Gulpin,
	Swalot,
	Carvanha,
	Sharpedo,
	Wailmer,
	Wailord,
	Numel,
	Camerupt,
	Torkoal,
	Spoink,
	Grumpig,
	Spinda,
	Trapinch,
	Vibrava,
	Flygon,
	Cacnea,
	Cacturne,
	Swablu,
	Altaria,
	Zangoose,
	Seviper,
	Lunatone,
	Solrock,
	Barboach,
	Whiscash,
	Corphish,
	Crawdaunt,
	Baltoy,
	Claydol,
	Lileep,
	Cradily,
	Anorith,
	Armaldo,
	Feebas,
	Milotic,
	Castform,
	Kecleon,
	Shuppet,
	Banette,
	Duskull,
	Dusclops,
	Tropius,
	Chimecho,
	Absol,
	Wynaut,
	Snorunt,
	Glalie,
	Spheal,
	Sealeo,
	Walrein,
	Clamperl,
	Huntail,
	Gorebyss,
	Relicanth,
	Luvdisc,
	Bagon,
	Shelgon,
	Salamence,
	Beldum,
	Metang,
	Metagross,
	Regirock,
	Regice,
	Registeel,
	Latias,
	Latios,
	Kyogre,
	Groudon,
	Rayquaza,
	Jirachi,
	Deoxys_Mediocre,
	Deoxys_Attack,
	Deoxys_Defense,
	Deoxys_Speed,
	Generation_3_End,
	
	// Generation 4
	Turtwig = Generation_3_End,
	Grotle,
	Torterra,
	Chimchar,
	Monferno,
	Infernape,
	Piplup,
	Prinplup,
	Empoleon,
	Starly,
	Staravia,
	Staraptor,
	Bidoof,
	Bibarel,
	Kricketot,
	Kricketune,
	Shinx,
	Luxio,
	Luxray,
	Budew,
	Roserade,
	Cranidos,
	Rampardos,
	Shieldon,
	Bastiodon,
	Burmy,
	Wormadam_Plant,
	Wormadam_Sandy,
	Wormadam_Trash,
	Mothim,
	Combee,
	Vespiquen,
	Pachirisu,
	Buizel,
	Floatzel,
	Cherubi,
	Cherrim,
	Shellos,
	Gastrodon,
	Ambipom,
	Drifloon,
	Drifblim,
	Buneary,
	Lopunny,
	Mismagius,
	Honchkrow,
	Glameow,
	Purugly,
	Chingling,
	Stunky,
	Skuntank,
	Bronzor,
	Bronzong,
	Bonsly,
	Mime_Jr,
	Happiny,
	Chatot,
	Spiritomb,
	Gible,
	Gabite,
	Garchomp,
	Munchlax,
	Riolu,
	Lucario,
	Hippopotas,
	Hippowdon,
	Skorupi,
	Drapion,
	Croagunk,
	Toxicroak,
	Carnivine,
	Finneon,
	Lumineon,
	Mantyke,
	Snover,
	Abomasnow,
	Weavile,
	Magnezone,
	Lickilicky,
	Rhyperior,
	Tangrowth,
	Electivire,
	Magmortar,
	Togekiss,
	Yanmega,
	Leafeon,
	Glaceon,
	Gliscor,
	Mamoswine,
	Porygon_Z,
	Gallade,
	Probopass,
	Dusknoir,
	Froslass,
	Rotom,
	Rotom_Heat,
	Rotom_Wash,
	Rotom_Frost,
	Rotom_Fan,
	Rotom_Mow,
	Uxie,
	Mesprit,
	Azelf,
	Dialga,
	Palkia,
	Heatran,
	Regigigas,
	Giratina_Altered,
	Giratina_Origin,
	Cresselia,
	Phione,
	Manaphy,
	Darkrai,
	Shaymin_Land,
	Shaymin_Sky,
	Arceus,
	Generation_4_End,
	
	// Generation 5
	Victini = Generation_4_End,
	Snivy,
	Servine,
	Serperior,
	Tepig,
	Pignite,
	Emboar,
	Oshawott,
	Dewott,
	Samurott,
	Patrat,
	Watchog,
	Lillipup,
	Herdier,
	Stoutland,
	Purrloin,
	Liepard,
	Pansage,
	Simisage,
	Pansear,
	Simisear,
	Panpour,
	Simipour,
	Munna,
	Musharna,
	Pidove,
	Tranquill,
	Unfezant,
	Blitzle,
	Zebstrika,
	Roggenrola,
	Boldore,
	Gigalith,
	Woobat,
	Swoobat,
	Drilbur,
	Excadrill,
	Audino,
	Timburr,
	Gurdurr,
	Conkeldurr,
	Tympole,
	Palpitoad,
	Seismitoad,
	Throh,
	Sawk,
	Sewaddle,
	Swadloon,
	Leavanny,
	Venipede,
	Whirlipede,
	Scolipede,
	Cottonee,
	Whimsicott,
	Petilil,
	Lilligant,
	Basculin_Red,
	Basculin_Blue,
	Sandile,
	Krokorok,
	Krookodile,
	Darumaka,
	Darmanitan,
	Maractus,
	Dwebble,
	Crustle,
	Scraggy,
	Scrafty,
	Sigilyph,
	Yamask,
	Cofagrigus,
	Tirtouga,
	Carracosta,
	Archen,
	Archeops,
	Trubbish,
	Garbodor,
	Zorua,
	Zoroark,
	Minccino,
	Cinccino,
	Gothita,
	Gothorita,
	Gothitelle,
	Solosis,
	Duosion,
	Reuniclus,
	Ducklett,
	Swanna,
	Vanillite,
	Vanillish,
	Vanilluxe,
	Deerling,
	Sawsbuck,
	Emolga,
	Karrablast,
	Escavalier,
	Foongus,
	Amoonguss,
	Frillish,
	Jellicent,
	Alomomola,
	Joltik,
	Galvantula,
	Ferroseed,
	Ferrothorn,
	Klink,
	Klang,
	Klinklang,
	Tynamo,
	Eelektrik,
	Eelektross,
	Elgyem,
	Beheeyem,
	Litwick,
	Lampent,
	Chandelure,
	Axew,
	Fraxure,
	Haxorus,
	Cubchoo,
	Beartic,
	Cryogonal,
	Shelmet,
	Accelgor,
	Stunfisk,
	Mienfoo,
	Mienshao,
	Druddigon,
	Golett,
	Golurk,
	Pawniard,
	Bisharp,
	Bouffalant,
	Rufflet,
	Braviary,
	Vullaby,
	Mandibuzz,
	Heatmor,
	Durant,
	Deino,
	Zweilous,
	Hydreigon,
	Larvesta,
	Volcarona,
	Cobalion,
	Terrakion,
	Virizion,
	Tornadus_Incarnate,
	Tornadus_Therian,
	Thundurus_Incarnate,
	Thundurus_Therian,
	Reshiram,
	Zekrom,
	Landorus_Incarnate,
	Landorus_Therian,
	Kyurem,
	Kyurem_Black,
	Kyurem_White,
	Keldeo,
	Meloetta,
	Genesect,
	Generation_5_End,
	END = Generation_5_End
};

constexpr auto number_of_species = static_cast<unsigned>(Species::END);
inline Species & operator++(Species & species) {
	species = static_cast<Species>(static_cast<unsigned>(species) + 1);
	return species;
}

constexpr auto hash(Species const species) noexcept {
	return bounded::integer<0, static_cast<intmax_t>(Species::END)>(species);
}
constexpr auto max_hash(Species) noexcept {
	return bounded::make<static_cast<intmax_t>(Species::END)>();
}

}	// namespace technicalmachine
#endif	// POKEMON__SPECIES_HPP_
