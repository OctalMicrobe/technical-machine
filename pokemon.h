// Pokemon data structure
// Copyright 2011 David Stone
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License
// as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef POKEMON_H_
#define POKEMON_H_

#include <map>
#include <string>
#include <vector>
#include "ability.h"
#include "active.h"
#include "gender.h"
#include "item.h"
#include "move.h"
#include "species.h"
#include "stat.h"
#include "status.h"
#include "type.h"

namespace technicalmachine {

class Pokemon {
	public:
		std::string nickname;
		species name;
		abilities ability;
		genders gender;
		items item;
		statuses status;
		types type1;
		types type2;
		Vanish vanish;
	//	std::vector<Move> moveset;
	//	std::vector<Move>::iterator move;			// The move currently being used
		Active<Move> move;
		Stat hp;
		Stat atk;
		Stat def;
		Stat spa;
		Stat spd;
		Stat spe;
		natures nature;
		short bide_damage;
		char bide;
		char confused;
		char embargo;
		char encore;
		char heal_block;
		char level;
		char magnet_rise;
		char mass;		// mass == power of Grass Knot / Low Kick, not the actual mass stat
		char partial_trap;		// Number of turns remaining on Bind, Clamp, Fire Spin, Magma Storm, Sand Tomb, Whirlpool, and Wrap
		char perish_song;
		char rampage;			// Number of turns remaining on Outrage, Petal Dance, and Thrash
		char sleep;				// wakes up when this number is 2 through 5
		char slow_start;
		char stockpile;
		char taunt;
		char toxic;				// Number of turns this Pokemon has already taken Toxic damage (or would have if Magic Guard / Poison Heal weren't in play)
		char uproar;			// Number of turns remaining on Uproar
		char yawn;
		bool aqua_ring;
		bool attract;
		bool awaken;		// Will it wake up
		bool charge;
		bool curse;
		bool damaged;
		bool defense_curl;
		bool destiny_bond;
		bool ff;				// Flash Fire
		bool flinch;
		bool focus_energy;
		bool identified;
		bool imprison;			// Has this Pokemon used Imprison?
		bool ingrain;
		bool leech_seed;
		bool loaf;
		bool lock_on;
		bool mf;				// Me First
		bool minimize;
		bool moved;
		bool mud_sport;
		bool nightmare;
		bool roost;
		bool shed_skin;
		bool torment;
		bool trapped;			// Block, Mean Look, Spider Web
		bool water_sport;

		unsigned char happiness;
		char accuracy;
		char evasion;
	
		bool operator== (const Pokemon &other) const {
			if (this->move.set.size() != other.move.set.size())
				return false;
			for (size_t n = 0; n != this->move.set.size(); ++n) {
				if (this->move.set [n] == other.move.set [n])
					return false;
			}
			return this->name == other.name and this->status == other.status and this->vanish == other.vanish and this->bide == other.bide and this->confused == other.confused and this->embargo == other.embargo and this->encore == other.encore and this->heal_block == other.heal_block and this->magnet_rise == other.magnet_rise and this->partial_trap == other.partial_trap and this->perish_song == other.perish_song and this->rampage == other.rampage and this->sleep == other.sleep and this->slow_start == other.slow_start and this->stockpile == other.stockpile and this->taunt == other.taunt and this->toxic == other.toxic and this->uproar == other.yawn and this->aqua_ring == other.aqua_ring and this->attract == other.attract and this->charge == other.charge and this->curse == other.curse and this->defense_curl == other.defense_curl and this->destiny_bond == other.destiny_bond and this->ff == other.ff and this->focus_energy == other.focus_energy and this->identified == other.identified and this->imprison == other.imprison and this->ingrain == other.ingrain and this->leech_seed == other.leech_seed and this->loaf == other.loaf and this->lock_on == other.lock_on and this->minimize == other.minimize and this->mud_sport == other.mud_sport and this->nightmare == other.nightmare and this->torment == other.torment and this->trapped == other.trapped and this->water_sport == other.water_sport and this->accuracy == other.accuracy and this->evasion == other.evasion and this->hp.stat == other.hp.stat and this->atk.stage == other.atk.stage and this->def.stage == other.def.stage and this->spa.stage == other.spa.stage and this->spd.stage == other.spd.stage and this->spe.stage == other.spe.stage and this->item == other.item;
		}
		bool operator!= (const Pokemon &other) const {
			return !(*this == other);
		}
		Pokemon (const species &member);
};

const types get_pokemon_type [][2] = {
{ GRASS, ICE },				// Abomasnow
{ PSYCHIC_TYPE, TYPELESS },		// Abra
{ DARK, TYPELESS },			// Absol
{ ROCK, FLYING },			// Aerodactyl
{ STEEL, ROCK },			// Aggron
{ NORMAL, TYPELESS },		// Aipom
{ PSYCHIC_TYPE, TYPELESS },		// Alakazam
{ DRAGON, FLYING },			// Altaria
{ NORMAL, TYPELESS },		// Ambipom
{ ELECTRIC, TYPELESS },		// Ampharos
{ ROCK, BUG },				// Anorith
{ POISON, TYPELESS },		// Arbok
{ FIRE, TYPELESS },			// Arcanine
{ NORMAL, TYPELESS },		// Arceus
{ BUG, POISON },			// Ariados
{ ROCK, BUG },				// Armaldo
{ STEEL, ROCK },			// Aron
{ ICE, FLYING },			// Articuno
{ PSYCHIC_TYPE, TYPELESS },		// Azelf
{ WATER, TYPELESS },		// Azumarill
{ NORMAL, TYPELESS },		// Azurill
{ DRAGON, TYPELESS },		// Bagon
{ GROUND, PSYCHIC_TYPE },		// Baltoy
{ GHOST, TYPELESS },		// Banette
{ WATER, GROUND },			// Barboach
{ ROCK, STEEL },			// Bastiodon
{ GRASS, TYPELESS },		// Bayleef
{ BUG, FLYING },			// Beautifly
{ BUG, POISON },			// Beedrill
{ STEEL, PSYCHIC_TYPE },			// Beldum
{ GRASS, TYPELESS },		// Bellossom
{ GRASS, POISON },			// Bellsprout
{ NORMAL, WATER },			// Bibarel
{ NORMAL, TYPELESS },		// Bidoof
{ WATER, TYPELESS },		// Blastoise
{ FIRE, FIGHTING },			// Blaziken
{ NORMAL, TYPELESS },		// Blissey
{ ROCK, TYPELESS },			// Bonsly
{ GRASS, FIGHTING },		// Breloom
{ STEEL, PSYCHIC_TYPE },			// Bronzong
{ STEEL, PSYCHIC_TYPE },			// Bronzor
{ GRASS, POISON },			// Budew
{ WATER, TYPELESS },		// Buizel
{ GRASS, POISON },			// Bulbasaur
{ NORMAL, TYPELESS },		// Buneary
{ BUG, TYPELESS },			// Burmy
{ BUG, FLYING },			// Butterfree
{ GRASS, TYPELESS },		// Cacnea
{ GRASS, DARK },			// Cacturne
{ FIRE, GROUND },			// Camerupt
{ GRASS, TYPELESS },		// Carnivine
{ WATER, DARK },			// Carvanha
{ BUG, TYPELESS },			// Cascoon
{ NORMAL, TYPELESS },		// Castform
{ BUG, TYPELESS },			// Caterpie
{ PSYCHIC_TYPE, GRASS },			// Celebi
{ NORMAL, TYPELESS },		// Chansey
{ FIRE, FLYING },			// Charizard
{ FIRE, TYPELESS },			// Charmander
{ FIRE, TYPELESS },			// Charmeleon
{ NORMAL, FLYING },			// Chatot
{ GRASS, TYPELESS },		// Cherrim
{ GRASS, TYPELESS },		// Cherubi
{ GRASS, TYPELESS },		// Chikorita
{ FIRE, TYPELESS },			// Chimchar
{ PSYCHIC_TYPE, TYPELESS },		// Chimecho
{ WATER, ELECTRIC },		// Chinchou
{ PSYCHIC_TYPE, TYPELESS },		// Chingling
{ WATER, TYPELESS },		// Clamperl
{ GROUND, PSYCHIC_TYPE },		// Claydol
{ NORMAL, TYPELESS },		// Clefable
{ NORMAL, TYPELESS },		// Clefairy
{ NORMAL, TYPELESS },		// Cleffa
{ WATER, ICE },				// Cloyster
{ BUG, FLYING },			// Combee
{ FIRE, FIGHTING },			// Combusken
{ WATER, TYPELESS },		// Corphish
{ WATER, ROCK },			// Corsola
{ ROCK, GRASS },			// Cradily
{ ROCK, TYPELESS },			// Cranidos
{ WATER, DARK },			// Crawdaunt
{ PSYCHIC_TYPE, TYPELESS },		// Cresselia
{ POISON, FIGHTING },		// Croagunk
{ POISON, FLYING },			// Crobat
{ WATER, TYPELESS },		// Croconaw
{ GROUND, TYPELESS },		// Cubone
{ FIRE, TYPELESS },			// Cyndaquil
{ DARK, TYPELESS },			// Darkrai
{ NORMAL, TYPELESS },		// Delcatty
{ ICE, FLYING },			// Delibird
{ PSYCHIC_TYPE, TYPELESS },		// Deoxys-A
{ PSYCHIC_TYPE, TYPELESS },		// Deoxys-D
{ PSYCHIC_TYPE, TYPELESS },		// Deoxys-M
{ PSYCHIC_TYPE, TYPELESS },		// Deoxys-S
{ WATER, ICE },				// Dewgong
{ STEEL, DRAGON },			// Dialga
{ GROUND, TYPELESS },		// Diglett
{ NORMAL, TYPELESS },		// Ditto
{ NORMAL, FLYING },			// Dodrio
{ NORMAL, FLYING },			// Doduo
{ GROUND, TYPELESS },		// Donphan
{ DRAGON, TYPELESS },		// Dragonair
{ DRAGON, FLYING },			// Dragonite
{ POISON, DARK },			// Drapion
{ DRAGON, TYPELESS },		// Dratini
{ GHOST, FLYING },			// Drifblim
{ GHOST, FLYING },			// Drifloon
{ PSYCHIC_TYPE, TYPELESS },		// Drowzee
{ GROUND, TYPELESS },		// Dugtrio
{ NORMAL, TYPELESS },		// Dunsparce
{ GHOST, TYPELESS },		// Dusclops
{ GHOST, TYPELESS },		// Dusknoir
{ GHOST, TYPELESS },		// Duskull
{ BUG, POISON },			// Dustox
{ NORMAL, TYPELESS },		// Eevee
{ POISON, TYPELESS },		// Ekans
{ ELECTRIC, TYPELESS },		// Electabuzz
{ ELECTRIC, TYPELESS },		// Electivire
{ ELECTRIC, TYPELESS },		// Electrike
{ ELECTRIC, TYPELESS },		// Electrode
{ ELECTRIC, TYPELESS },		// Elekid
{ WATER, STEEL },			// Empoleon
{ FIRE, TYPELESS },			// Entei
{ PSYCHIC_TYPE, TYPELESS },		// Espeon
{ GRASS, PSYCHIC_TYPE },			// Exeggcute
{ GRASS, PSYCHIC_TYPE },			// Exeggutor
{ NORMAL, TYPELESS },		// Exploud
{ NORMAL, FLYING },			// Farfetch'd
{ NORMAL, FLYING },			// Fearow
{ WATER, TYPELESS },		// Feebas
{ WATER, TYPELESS },		// Feraligatr
{ WATER, TYPELESS },		// Finneon
{ ELECTRIC, TYPELESS },		// Flaaffy
{ FIRE, TYPELESS },			// Flareon
{ WATER, TYPELESS },		// Floatzel
{ GROUND, DRAGON },			// Flygon
{ BUG, STEEL },				// Forretress
{ ICE, GHOST },				// Froslass
{ NORMAL, TYPELESS },		// Furret
{ DRAGON, GROUND },			// Gabite
{ PSYCHIC_TYPE, FIGHTING },		// Gallade
{ DRAGON, GROUND },			// Garchomp
{ PSYCHIC_TYPE, TYPELESS },		// Gardevoir
{ GHOST, POISON },			// Gastly
{ WATER, GROUND },			// Gastrodon
{ GHOST, POISON },			// Gengar
{ ROCK, GROUND },			// Geodude
{ DRAGON, GROUND },			// Gible
{ NORMAL, PSYCHIC_TYPE },		// Girafarig
{ GHOST, DRAGON },			// Giratina-A
{ GHOST, DRAGON },			// Giratina-O
{ ICE, TYPELESS },			// Glaceon
{ ICE, TYPELESS },			// Glalie
{ NORMAL, TYPELESS },		// Glameow
{ GROUND, FLYING },			// Gligar
{ GROUND, FLYING },			// Gliscor
{ GRASS, POISON },			// Gloom
{ POISON, FLYING },			// Golbat
{ WATER, TYPELESS },		// Goldeen
{ WATER, TYPELESS },		// Golduck
{ ROCK, GROUND },			// Golem
{ WATER, TYPELESS },		// Gorebyss
{ NORMAL, TYPELESS },		// Granbull
{ ROCK, GROUND },			// Graveler
{ POISON, TYPELESS },		// Grimer
{ GRASS, TYPELESS },		// Grotle
{ GROUND, TYPELESS },		// Groudon
{ GRASS, TYPELESS },		// Grovyle
{ FIRE, TYPELESS },			// Growlithe
{ PSYCHIC_TYPE, TYPELESS },		// Grumpig
{ POISON, TYPELESS },		// Gulpin
{ WATER, FLYING },			// Gyarados
{ NORMAL, TYPELESS },		// Happiny
{ FIGHTING, TYPELESS },		// Hariyama
{ GHOST, POISON },			// Haunter
{ FIRE, STEEL },			// Heatran
{ BUG, FIGHTING },			// Heracross
{ GROUND, TYPELESS },		// Hippopotas
{ GROUND, TYPELESS },		// Hippowdon
{ FIGHTING, TYPELESS },		// Hitmonchan
{ FIGHTING, TYPELESS },		// Hitmonlee
{ FIGHTING, TYPELESS },		// Hitmontop
{ FIRE, FLYING },			// Ho-Oh
{ DARK, FLYING },			// Honchkrow
{ NORMAL, FLYING },			// Hoothoot
{ GRASS, FLYING },			// Hoppip
{ WATER, TYPELESS },		// Horsea
{ DARK, FIRE },				// Houndoom
{ DARK, FIRE },				// Houndour
{ WATER, TYPELESS },		// Huntail
{ PSYCHIC_TYPE, TYPELESS },		// Hypno
{ NORMAL, TYPELESS },		// Igglybuff
{ BUG, TYPELESS },			// Illumise
{ FIRE, FIGHTING },			// Infernape
{ GRASS, POISON },			// Ivysaur
{ NORMAL, TYPELESS },		// Jigglypuff
{ STEEL, PSYCHIC_TYPE },			// Jirachi
{ ELECTRIC, TYPELESS },		// Jolteon
{ GRASS, FLYING },			// Jumpluff
{ ICE, PSYCHIC_TYPE },			// Jynx
{ ROCK, WATER },			// Kabuto
{ ROCK, WATER },			// Kabutops
{ PSYCHIC_TYPE, TYPELESS },		// Kadabra
{ BUG, POISON },			// Kakuna
{ NORMAL, TYPELESS },		// Kangaskhan
{ NORMAL, TYPELESS },		// Kecleon
{ WATER, DRAGON },			// Kingdra
{ WATER, TYPELESS },		// Kingler
{ PSYCHIC_TYPE, TYPELESS },		// Kirlia
{ POISON, TYPELESS },		// Koffing
{ WATER, TYPELESS },		// Krabby
{ BUG, TYPELESS },			// Kricketot
{ BUG, TYPELESS },			// Kricketune
{ WATER, TYPELESS },		// Kyogre
{ STEEL, ROCK },			// Lairon
{ WATER, ELECTRIC },		// Lanturn
{ WATER, ICE },				// Lapras
{ ROCK, GROUND },			// Larvitar
{ DRAGON, PSYCHIC_TYPE },		// Latias
{ DRAGON, PSYCHIC_TYPE },		// Latios
{ GRASS, TYPELESS },		// Leafeon
{ BUG, FLYING },			// Ledian
{ BUG, FLYING },			// Ledyba
{ NORMAL, TYPELESS },		// Lickilicky
{ NORMAL, TYPELESS },		// Lickitung
{ ROCK, GRASS },			// Lileep
{ NORMAL, TYPELESS },		// Linoone
{ WATER, GRASS },			// Lombre
{ NORMAL, TYPELESS },		// Lopunny
{ WATER, GRASS },			// Lotad
{ NORMAL, TYPELESS },		// Loudred
{ FIGHTING, STEEL },		// Lucario
{ WATER, GRASS },			// Ludicolo
{ PSYCHIC_TYPE, FLYING },		// Lugia
{ WATER, TYPELESS },		// Lumineon
{ ROCK, PSYCHIC_TYPE },			// Lunatone
{ WATER, TYPELESS },		// Luvdisc
{ ELECTRIC, TYPELESS },		// Luxio
{ ELECTRIC, TYPELESS },		// Luxray
{ FIGHTING, TYPELESS },		// Machamp
{ FIGHTING, TYPELESS },		// Machoke
{ FIGHTING, TYPELESS },		// Machop
{ FIRE, TYPELESS },			// Magby
{ FIRE, ROCK },				// Magcargo
{ WATER, TYPELESS },		// Magikarp
{ FIRE, TYPELESS },			// Magmar
{ FIRE, TYPELESS },			// Magmortar
{ ELECTRIC, STEEL },		// Magnemite
{ ELECTRIC, STEEL },		// Magneton
{ ELECTRIC, STEEL },		// Magnezone
{ FIGHTING, TYPELESS },		// Makuhita
{ ICE, GROUND },			// Mamoswine
{ WATER, TYPELESS },		// Manaphy
{ ELECTRIC, TYPELESS },		// Manectric
{ FIGHTING, TYPELESS },		// Mankey
{ WATER, FLYING },			// Mantine
{ WATER, FLYING },			// Mantyke
{ ELECTRIC, TYPELESS },		// Mareep
{ WATER, TYPELESS },		// Marill
{ GROUND, TYPELESS },		// Marowak
{ WATER, GROUND },			// Marshtomp
{ BUG, FLYING },			// Masquerain
{ STEEL, TYPELESS },		// Mawile
{ FIGHTING, PSYCHIC_TYPE },		// Medicham
{ FIGHTING, PSYCHIC_TYPE },		// Meditite
{ GRASS, TYPELESS },		// Meganium
{ NORMAL, TYPELESS },		// Meowth
{ PSYCHIC_TYPE, TYPELESS },		// Mesprit
{ STEEL, PSYCHIC_TYPE },			// Metagross
{ STEEL, PSYCHIC_TYPE },			// Metang
{ BUG, TYPELESS },			// Metapod
{ PSYCHIC_TYPE, TYPELESS },		// Mew
{ PSYCHIC_TYPE, TYPELESS },		// Mewtwo
{ DARK, TYPELESS },			// Mightyena
{ WATER, TYPELESS },		// Milotic
{ NORMAL, TYPELESS },		// Miltank
{ PSYCHIC_TYPE, TYPELESS },		// Mime Jr.
{ ELECTRIC, TYPELESS },		// Minun
{ GHOST, TYPELESS },		// Misdreavus
{ GHOST, TYPELESS },		// Mismagius
{ FIRE, FLYING },			// Moltres
{ FIRE, FIGHTING },			// Monferno
{ BUG, FLYING },			// Mothim
{ PSYCHIC_TYPE, TYPELESS },		// Mr. Mime
{ WATER, TYPELESS },		// Mudkip
{ POISON, TYPELESS },		// Muk
{ NORMAL, TYPELESS },		// Munchlax
{ DARK, FLYING },			// Murkrow
{ PSYCHIC_TYPE, FLYING },		// Natu
{ POISON, GROUND },			// Nidoking
{ POISON, GROUND },			// Nidoqueen
{ POISON, TYPELESS },		// Nidoran-F
{ POISON, TYPELESS },		// Nidoran-M
{ POISON, TYPELESS },		// Nidorina
{ POISON, TYPELESS },		// Nidorino
{ BUG, GROUND },			// Nincada
{ FIRE, TYPELESS },			// Ninetales
{ BUG, FLYING },			// Ninjask
{ NORMAL, FLYING },			// Noctowl
{ ROCK, TYPELESS },			// Nosepass
{ FIRE, GROUND },			// Numel
{ GRASS, DARK },			// Nuzleaf
{ WATER, TYPELESS },		// Octillery
{ GRASS, POISON },			// Oddish
{ ROCK, WATER },			// Omanyte
{ ROCK, WATER },			// Omastar
{ ROCK, GROUND },			// Onix
{ ELECTRIC, TYPELESS },		// Pachirisu
{ WATER, DRAGON },			// Palkia
{ BUG, GRASS },				// Paras
{ BUG, GRASS },				// Parasect
{ WATER, FLYING },			// Pelipper
{ NORMAL, TYPELESS },		// Persian
{ GROUND, TYPELESS },		// Phanpy
{ WATER, TYPELESS },		// Phione
{ ELECTRIC, TYPELESS },		// Pichu
{ NORMAL, FLYING },			// Pidgeot
{ NORMAL, FLYING },			// Pidgeotto
{ NORMAL, FLYING },			// Pidgey
{ ELECTRIC, TYPELESS },		// Pikachu
{ ICE, GROUND },			// Piloswine
{ BUG, TYPELESS },			// Pineco
{ BUG, TYPELESS },			// Pinsir
{ WATER, TYPELESS },		// Piplup
{ ELECTRIC, TYPELESS },		// Plusle
{ WATER, TYPELESS },		// Politoed
{ WATER, TYPELESS },		// Poliwag
{ WATER, TYPELESS },		// Poliwhirl
{ WATER, FIGHTING },		// Poliwrath
{ FIRE, TYPELESS },			// Ponyta
{ DARK, TYPELESS },			// Poochyena
{ NORMAL, TYPELESS },		// Porygon
{ NORMAL, TYPELESS },		// Porygon-Z
{ NORMAL, TYPELESS },		// Porygon2
{ FIGHTING, TYPELESS },		// Primeape
{ WATER, TYPELESS },		// Prinplup
{ ROCK, STEEL },			// Probopass
{ WATER, TYPELESS },		// Psyduck
{ ROCK, GROUND },			// Pupitar
{ NORMAL, TYPELESS },		// Purugly
{ WATER, GROUND },			// Quagsire
{ FIRE, TYPELESS },			// Quilava
{ WATER, POISON },			// Qwilfish
{ ELECTRIC, TYPELESS },		// Raichu
{ ELECTRIC, TYPELESS },		// Raikou
{ PSYCHIC_TYPE, TYPELESS },		// Ralts
{ ROCK, TYPELESS },			// Rampardos
{ FIRE, TYPELESS },			// Rapidash
{ NORMAL, TYPELESS },		// Raticate
{ NORMAL, TYPELESS },		// Rattata
{ DRAGON, FLYING },			// Rayquaza
{ ICE, TYPELESS },			// Regice
{ NORMAL, TYPELESS },		// Regigigas
{ ROCK, TYPELESS },			// Regirock
{ STEEL, TYPELESS },		// Registeel
{ WATER, ROCK },			// Relicanth
{ WATER, TYPELESS },		// Remoraid
{ GROUND, ROCK },			// Rhydon
{ GROUND, ROCK },			// Rhyhorn
{ GROUND, ROCK },			// Rhyperior
{ FIGHTING, TYPELESS },		// Riolu
{ GRASS, POISON },			// Roselia
{ GRASS, POISON },			// Roserade
{ ELECTRIC, GHOST },		// Rotom
{ ELECTRIC, GHOST },		// Rotom-C
{ ELECTRIC, GHOST },		// Rotom-F
{ ELECTRIC, GHOST },		// Rotom-H
{ ELECTRIC, GHOST },		// Rotom-S
{ ELECTRIC, GHOST },		// Rotom-W
{ DARK, GHOST },			// Sableye
{ DRAGON, FLYING },			// Salamence
{ GROUND, TYPELESS },		// Sandshrew
{ GROUND, TYPELESS },		// Sandslash
{ GRASS, TYPELESS },		// Sceptile
{ BUG, STEEL },				// Scizor
{ BUG, FLYING },			// Scyther
{ WATER, TYPELESS },		// Seadra
{ WATER, TYPELESS },		// Seaking
{ ICE, WATER },				// Sealeo
{ GRASS, TYPELESS },		// Seedot
{ WATER, TYPELESS },		// Seel
{ NORMAL, TYPELESS },		// Sentret
{ POISON, TYPELESS },		// Seviper
{ WATER, DARK },			// Sharpedo
{ GRASS, TYPELESS },		// Shaymin-L
{ GRASS, FLYING },			// Shaymin-S
{ BUG, GHOST },				// Shedinja
{ DRAGON, TYPELESS },		// Shelgon
{ WATER, TYPELESS },		// Shellder
{ WATER, TYPELESS },		// Shellos
{ ROCK, STEEL },			// Shieldon
{ GRASS, DARK },			// Shiftry
{ ELECTRIC, TYPELESS },		// Shinx
{ GRASS, TYPELESS },		// Shroomish
{ BUG, ROCK },				// Shuckle
{ GHOST, TYPELESS },		// Shuppet
{ BUG, TYPELESS },			// Silcoon
{ STEEL, FLYING },			// Skarmory
{ GRASS, FLYING },			// Skiploom
{ NORMAL, TYPELESS },		// Skitty
{ POISON, BUG },			// Skorupi
{ POISON, DARK },			// Skuntank
{ NORMAL, TYPELESS },		// Slaking
{ NORMAL, TYPELESS },		// Slakoth
{ WATER, PSYCHIC_TYPE },			// Slowbro
{ WATER, PSYCHIC_TYPE },			// Slowking
{ WATER, PSYCHIC_TYPE },			// Slowpoke
{ FIRE, TYPELESS },			// Slugma
{ NORMAL, TYPELESS },		// Smeargle
{ ICE, PSYCHIC_TYPE },			// Smoochum
{ DARK, ICE },				// Sneasel
{ NORMAL, TYPELESS },		// Snorlax
{ ICE, TYPELESS },			// Snorunt
{ GRASS, ICE },				// Snover
{ NORMAL, TYPELESS },		// Snubbull
{ ROCK, PSYCHIC_TYPE },			// Solrock
{ NORMAL, FLYING },			// Spearow
{ ICE, WATER },				// Spheal
{ BUG, POISON },			// Spinarak
{ NORMAL, TYPELESS },		// Spinda
{ GHOST, DARK },			// Spiritomb
{ PSYCHIC_TYPE, TYPELESS },		// Spoink
{ WATER, TYPELESS },		// Squirtle
{ NORMAL, TYPELESS },		// Stantler
{ NORMAL, FLYING },			// Staraptor
{ NORMAL, FLYING },			// Staravia
{ NORMAL, FLYING },			// Starly
{ WATER, PSYCHIC_TYPE },			// Starmie
{ WATER, TYPELESS },		// Staryu
{ STEEL, GROUND },			// Steelix
{ POISON, DARK },			// Stunky
{ ROCK, TYPELESS },			// Sudowoodo
{ WATER, TYPELESS },		// Suicune
{ GRASS, TYPELESS },		// Sunflora
{ GRASS, TYPELESS },		// Sunkern
{ BUG, WATER },				// Surskit
{ NORMAL, FLYING },			// Swablu
{ POISON, TYPELESS },		// Swalot
{ WATER, GROUND },			// Swampert
{ NORMAL, FLYING },			// Swellow
{ ICE, GROUND },			// Swinub
{ NORMAL, FLYING },			// Taillow
{ GRASS, TYPELESS },		// Tangela
{ GRASS, TYPELESS },		// Tangrowth
{ NORMAL, TYPELESS },		// Tauros
{ NORMAL, TYPELESS },		// Teddiursa
{ WATER, POISON },			// Tentacool
{ WATER, POISON },			// Tentacruel
{ NORMAL, FLYING },			// Togekiss
{ NORMAL, TYPELESS },		// Togepi
{ NORMAL, FLYING },			// Togetic
{ FIRE, TYPELESS },			// Torchic
{ FIRE, TYPELESS },			// Torkoal
{ GRASS, GROUND },			// Torterra
{ WATER, TYPELESS },		// Totodile
{ POISON, FIGHTING },		// Toxicroak
{ GROUND, TYPELESS },		// Trapinch
{ GRASS, TYPELESS },		// Treecko
{ GRASS, FLYING },			// Tropius
{ GRASS, TYPELESS },		// Turtwig
{ FIRE, TYPELESS },			// Typhlosion
{ ROCK, DARK },				// Tyranitar
{ FIGHTING, TYPELESS },		// Tyrogue
{ DARK, TYPELESS },			// Umbreon
{ PSYCHIC_TYPE, TYPELESS },		// Unown
{ NORMAL, TYPELESS },		// Ursaring
{ PSYCHIC_TYPE, TYPELESS },		// Uxie
{ WATER, TYPELESS },		// Vaporeon
{ BUG, POISON },			// Venomoth
{ BUG, POISON },			// Venonat
{ GRASS, POISON },			// Venusaur
{ BUG, FLYING },			// Vespiquen
{ GROUND, DRAGON },			// Vibrava
{ GRASS, POISON },			// Victreebel
{ NORMAL, TYPELESS },		// Vigoroth
{ GRASS, POISON },			// Vileplume
{ BUG, TYPELESS },			// Volbeat
{ ELECTRIC, TYPELESS },		// Voltorb
{ FIRE, TYPELESS },			// Vulpix
{ WATER, TYPELESS },		// Wailmer
{ WATER, TYPELESS },		// Wailord
{ ICE, WATER },				// Walrein
{ WATER, TYPELESS },		// Wartortle
{ DARK, ICE },				// Weavile
{ BUG, POISON },			// Weedle
{ GRASS, POISON },			// Weepinbell
{ POISON, TYPELESS },		// Weezing
{ WATER, GROUND },			// Whiscash
{ NORMAL, TYPELESS },		// Whismur
{ NORMAL, TYPELESS },		// Wigglytuff
{ WATER, FLYING },			// Wingull
{ PSYCHIC_TYPE, TYPELESS },		// Wobbuffet
{ WATER, GROUND },			// Wooper
{ BUG, GRASS },				// Wormadam-P
{ BUG, GROUND },			// Wormadam-S
{ BUG, STEEL },				// Wormadam-T
{ BUG, TYPELESS },			// Wurmple
{ PSYCHIC_TYPE, TYPELESS },		// Wynaut
{ PSYCHIC_TYPE, FLYING },		// Xatu
{ BUG, FLYING },			// Yanma
{ BUG, FLYING },			// Yanmega
{ NORMAL, TYPELESS },		// Zangoose
{ ELECTRIC, FLYING },		// Zapdos
{ NORMAL, TYPELESS },		// Zigzagoon
{ POISON, FLYING }			// Zubat
};

const char get_mass [] = {
100,	// Abomasnow
40,	// Abra
60,	// Absol
80,	// Aerodactyl
120,	// Aggron
40,	// Aipom
60,	// Alakazam
40,	// Altaria
40,	// Ambipom
80,	// Ampharos
40,	// Anorith
80,	// Arbok
100,	// Arcanine
120,	// Arceus
60,	// Ariados
80,	// Armaldo
80,	// Aron
80,	// Articuno
20,	// Azelf
60,	// Azumarill
20,	// Azurill
60,	// Bagon
40,	// Baltoy
40,	// Banette
20,	// Barboach
100,	// Bastiodon
40,	// Bayleef
60,	// Beautifly
60,	// Beedrill
80,	// Beldum
20,	// Bellossom
20,	// Bellsprout
60,	// Bibarel
40,	// Bidoof
80,	// Blastoise
80,	// Blaziken
60,	// Blissey
40,	// Bonsly
60,	// Breloom
100,	// Bronzong
80,	// Bronzor
20,	// Budew
60,	// Buizel
20,	// Bulbasaur
20,	// Buneary
20,	// Burmy
60,	// Butterfree
80,	// Cacnea
80,	// Cacturne
120,	// Camerupt
60,	// Carnivine
40,	// Carvanha
40,	// Cascoon
20,	// Castform
20,	// Caterpie
20,	// Celebi
60,	// Chansey
80,	// Charizard
20,	// Charmander
40,	// Charmeleon
20,	// Chatot
20,	// Cherrim
20,	// Cherubi
20,	// Chikorita
20,	// Chimchar
20,	// Chimecho
40,	// Chinchou
20,	// Chingling
80,	// Clamperl
100,	// Claydol
60,	// Clefable
20,	// Clefairy
20,	// Cleffa
100,	// Cloyster
20,	// Combee
40,	// Combusken
40,	// Corphish
20,	// Corsola
80,	// Cradily
60,	// Cranidos
60,	// Crawdaunt
80,	// Cresselia
40,	// Croagunk
80,	// Crobat
40,	// Croconaw
20,	// Cubone
20,	// Cyndaquil
80,	// Darkrai
60,	// Delcatty
40,	// Delibird
80,	// Deoxys-A
80,	// Deoxys-D
80,	// Deoxys-M
80,	// Deoxys-S
100,	// Dewgong
120,	// Dialga
20,	// Diglett
20,	// Ditto
80,	// Dodrio
60,	// Doduo
100,	// Donphan
40,	// Dragonair
120,	// Dragonite
80,	// Drapion
20,	// Dratini
40,	// Drifblim
20,	// Drifloon
60,	// Drowzee
60,	// Dugtrio
40,	// Dunsparce
60,	// Dusclops
100,	// Dusknoir
40,	// Duskull
60,	// Dustox
20,	// Eevee
20,	// Ekans
60,	// Electabuzz
100,	// Electivire
40,	// Electrike
80,	// Electrode
40,	// Elekid
80,	// Empoleon
100,	// Entei
60,	// Espeon
20,	// Exeggcute
100,	// Exeggutor
80,	// Exploud
40,	// Farfetch'd
60,	// Fearow
20,	// Feebas
80,	// Feraligatr
20,	// Finneon
40,	// Flaaffy
40,	// Flareon
60,	// Floatzel
80,	// Flygon
100,	// Forretress
60,	// Froslass
60,	// Furret
80,	// Gabite
80,	// Gallade
80,	// Garchomp
60,	// Gardevoir
20,	// Gastly
60,	// Gastrodon
60,	// Gengar
40,	// Geodude
40,	// Gible
60,	// Girafarig
120,	// Giratina-A
120,	// Giratina-O
60,	// Glaceon
120,	// Glalie
20,	// Glameow
80,	// Gligar
60,	// Gliscor
20,	// Gloom
80,	// Golbat
40,	// Goldeen
80,	// Golduck
120,	// Golem
40,	// Gorebyss
60,	// Granbull
100,	// Graveler
60,	// Grimer
80,	// Grotle
120,	// Groudon
40,	// Grovyle
40,	// Growlithe
80,	// Grumpig
40,	// Gulpin
120,	// Gyarados
40,	// Happiny
120,	// Hariyama
20,	// Haunter
120,	// Heatran
80,	// Heracross
60,	// Hippopotas
120,	// Hippowdon
80,	// Hitmonchan
60,	// Hitmonlee
60,	// Hitmontop
100,	// Ho-Oh
60,	// Honchkrow
40,	// Hoothoot
20,	// Hoppip
20,	// Horsea
60,	// Houndoom
40,	// Houndour
60,	// Huntail
80,	// Hypno
20,	// Igglybuff
40,	// Illumise
80,	// Infernape
40,	// Ivysaur
20,	// Jigglypuff
20,	// Jirachi
40,	// Jolteon
20,	// Jumpluff
60,	// Jynx
40,	// Kabuto
60,	// Kabutops
80,	// Kadabra
20,	// Kakuna
80,	// Kangaskhan
40,	// Kecleon
100,	// Kingdra
80,	// Kingler
40,	// Kirlia
20,	// Koffing
20,	// Krabby
20,	// Kricketot
60,	// Kricketune
120,	// Kyogre
100,	// Lairon
40,	// Lanturn
120,	// Lapras
80,	// Larvitar
60,	// Latias
80,	// Latios
60,	// Leafeon
60,	// Ledian
40,	// Ledyba
100,	// Lickilicky
80,	// Lickitung
40,	// Lileep
60,	// Linoone
60,	// Lombre
60,	// Lopunny
20,	// Lotad
60,	// Loudred
80,	// Lucario
80,	// Ludicolo
120,	// Lugia
40,	// Lumineon
100,	// Lunatone
20,	// Luvdisc
60,	// Luxio
60,	// Luxray
100,	// Machamp
80,	// Machoke
40,	// Machop
40,	// Magby
80,	// Magcargo
20,	// Magikarp
60,	// Magmar
80,	// Magmortar
20,	// Magnemite
80,	// Magneton
100,	// Magnezone
80,	// Makuhita
120,	// Mamoswine
20,	// Manaphy
60,	// Manectric
60,	// Mankey
120,	// Mantine
80,	// Mantyke
20,	// Mareep
20,	// Marill
60,	// Marowak
60,	// Marshtomp
20,	// Masquerain
40,	// Mawile
60,	// Medicham
40,	// Meditite
100,	// Meganium
20,	// Meowth
20,	// Mesprit
120,	// Metagross
120,	// Metang
20,	// Metapod
20,	// Mew
100,	// Mewtwo
60,	// Mightyena
100,	// Milotic
80,	// Miltank
40,	// Mime Jr.
20,	// Minun
20,	// Misdreavus
20,	// Mismagius
80,	// Moltres
40,	// Monferno
40,	// Mothim
80,	// Mr. Mime
20,	// Mudkip
60,	// Muk
100,	// Munchlax
20,	// Murkrow
20,	// Natu
80,	// Nidoking
80,	// Nidoqueen
20,	// Nidoran♀
20,	// Nidoran♂
40,	// Nidorina
40,	// Nidorino
20,	// Nincada
40,	// Ninetales
40,	// Ninjask
60,	// Noctowl
80,	// Nosepass
40,	// Numel
60,	// Nuzleaf
60,	// Octillery
20,	// Oddish
20,	// Omanyte
60,	// Omastar
120,	// Onix
20,	// Pachirisu
120,	// Palkia
20,	// Paras
60,	// Parasect
60,	// Pelipper
60,	// Persian
60,	// Phanpy
20,	// Phione
20,	// Pichu
60,	// Pidgeot
60,	// Pidgeotto
20,	// Pidgey
20,	// Pikachu
80,	// Piloswine
20,	// Pineco
80,	// Pinsir
20,	// Piplup
20,	// Plusle
60,	// Politoed
40,	// Poliwag
40,	// Poliwhirl
80,	// Poliwrath
60,	// Ponyta
40,	// Poochyena
60,	// Porygon
60,	// Porygon-Z
60,	// Porygon2
60,	// Primeape
40,	// Prinplup
120,	// Probopass
40,	// Psyduck
100,	// Pupitar
60,	// Purugly
80,	// Quagsire
40,	// Quilava
20,	// Qwilfish
60,	// Raichu
100,	// Raikou
20,	// Ralts
100,	// Rampardos
80,	// Rapidash
40,	// Raticate
20,	// Rattata
120,	// Rayquaza
100,	// Regice
120,	// Regigigas
120,	// Regirock
120,	// Registeel
40,	// Relicanth
40,	// Remoraid
100,	// Rhydon
100,	// Rhyhorn
120,	// Rhyperior
40,	// Riolu
20,	// Roselia
40,	// Roserade
20,	// Rotom
20,	// Rotom-C
20,	// Rotom-F
20,	// Rotom-H
20,	// Rotom-S
20,	// Rotom-W
40,	// Sableye
100,	// Salamence
40,	// Sandshrew
60,	// Sandslash
80,	// Sceptile
100,	// Scizor
80,	// Scyther
40,	// Seadra
60,	// Seaking
80,	// Sealeo
20,	// Seedot
80,	// Seel
20,	// Sentret
80,	// Seviper
80,	// Sharpedo
20,	// Shaymin-L
20,	// Shaymin-S
20,	// Shedinja
100,	// Shelgon
20,	// Shellder
20,	// Shellos
80,	// Shieldon
80,	// Shiftry
20,	// Shinx
20,	// Shroomish
40,	// Shuckle
20,	// Shuppet
20,	// Silcoon
80,	// Skarmory
20,	// Skiploom
40,	// Skitty
40,	// Skorupi
60,	// Skuntank
100,	// Slaking
40,	// Slakoth
80,	// Slowbro
80,	// Slowking
60,	// Slowpoke
60,	// Slugma
80,	// Smeargle
20,	// Smoochum
60,	// Sneasel
120,	// Snorlax
40,	// Snorunt
80,	// Snover
20,	// Snubbull
100,	// Solrock
20,	// Spearow
60,	// Spheal
20,	// Spinarak
20,	// Spinda
100,	// Spiritomb
60,	// Spoink
20,	// Squirtle
80,	// Stantler
40,	// Staraptor
40,	// Staravia
20,	// Starly
80,	// Starmie
60,	// Staryu
120,	// Steelix
40,	// Stunky
60,	// Sudowoodo
100,	// Suicune
20,	// Sunflora
20,	// Sunkern
20,	// Surskit
20,	// Swablu
80,	// Swalot
80,	// Swampert
40,	// Swellow
20,	// Swinub
20,	// Taillow
60,	// Tangela
100,	// Tangrowth
80,	// Tauros
20,	// Teddiursa
60,	// Tentacool
80,	// Tentacruel
60,	// Togekiss
20,	// Togepi
20,	// Togetic
20,	// Torchic
80,	// Torkoal
120,	// Torterra
20,	// Totodile
60,	// Toxicroak
40,	// Trapinch
20,	// Treecko
80,	// Tropius
40,	// Turtwig
80,	// Typhlosion
120,	// Tyranitar
40,	// Tyrogue
60,	// Umbreon
20,	// Unown
100,	// Ursaring
20,	// Uxie
60,	// Vaporeon
40,	// Venomoth
60,	// Venonat
80,	// Venusaur
60,	// Vespiquen
40,	// Vibrava
40,	// Victreebel
60,	// Vigoroth
40,	// Vileplume
40,	// Volbeat
40,	// Voltorb
20,	// Vulpix
100,	// Wailmer
120,	// Wailord
100,	// Walrein
40,	// Wartortle
60,	// Weavile
20,	// Weedle
20,	// Weepinbell
20,	// Weezing
40,	// Whiscash
40,	// Whismur
40,	// Wigglytuff
20,	// Wingull
60,	// Wobbuffet
20,	// Wooper
20,	// Wormadam-P
20,	// Wormadam-S
20,	// Wormadam-T
20,	// Wurmple
40,	// Wynaut
40,	// Xatu
60,	// Yanma
80,	// Yanmega
60,	// Zangoose
80,	// Zapdos
40,	// Zigzagoon
20		// Zubat
};

void set_species_map (std::map <std::string, species> &species_map);

class Map {
	public:
		std::map <std::string, species> specie;
		std::map <std::string, genders> gender;
		std::map <std::string, natures> nature;
		std::map <std::string, items> item;
		std::map <std::string, abilities> ability;
		std::map <std::string, moves_list> move;
	
		Map ();
};

}
#endif
