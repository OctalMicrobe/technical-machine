// Move string conversions
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

#include "../move.hpp"

#include <cassert>
#include <map>
#include <string>

#include "invalid_string_conversion.hpp"

namespace technicalmachine {

std::string Move::to_string (Moves name) {
	assert(name <= END);
	std::string const name_to_string [] = {
		"Absorb", "Acid", "Acid Armor", "Acupressure", "Aerial Ace",
		"Aeroblast", "Agility", "Air Cutter", "Air Slash", "Amnesia",
		"AncientPower", "Aqua Jet", "Aqua Ring", "Aqua Tail", "Arm Thrust",
		"Aromatherapy", "Assist", "Assurance", "Astonish", "Attack Order",
		"Attract", "Aura Sphere", "Aurora Beam", "Avalanche", "Barrage",
		"Barrier", "Baton Pass", "Beat Up", "Belly Drum", "Bide",
		"Bind", "Bite", "Blast Burn", "Blaze Kick", "Blizzard",
		"Block", "Body Slam", "Bone Club", "Bone Rush", "Bonemerang",
		"Bounce", "Brave Bird", "Brick Break", "Brine", "Bubble",
		"BubbleBeam", "Bug Bite", "Bug Buzz", "Bulk Up", "Bullet Punch",
		"Bullet Seed", "Calm Mind", "Camouflage", "Captivate", "Charge",
		"Charge Beam", "Charm", "Chatter", "Clamp", "Close Combat",
		"Comet Punch", "Confuse Ray", "Confusion", "Constrict", "Conversion",
		"Conversion2", "Copycat", "Cosmic Power", "Cotton Spore", "Counter",
		"Covet", "Crabhammer", "Cross Chop", "Cross Poison", "Crunch",
		"Crush Claw", "Crush Grip", "Curse", "Cut", "Dark Pulse",
		"Dark Void", "Defend Order", "Defense Curl", "Defog", "Destiny Bond",
		"Detect", "Dig", "Disable", "Discharge", "Dive",
		"Dizzy Punch", "Doom Desire", "Double Hit", "Double Kick", "Double Team",
		"Double-Edge", "DoubleSlap", "Draco Meteor", "Dragon Claw", "Dragon Dance",
		"Dragon Pulse", "Dragon Rage", "Dragon Rush", "DragonBreath", "Drain Punch",
		"Dream Eater", "Drill Peck", "DynamicPunch", "Earth Power", "Earthquake",
		"Egg Bomb", "Embargo", "Ember", "Encore", "Endeavor",
		"Endure", "Energy Ball", "Eruption", "Explosion", "Extrasensory",
		"ExtremeSpeed", "Facade", "Faint Attack", "Fake Out", "Fake Tears",
		"False Swipe", "FeatherDance", "Feint", "Fire Blast", "Fire Fang",
		"Fire Punch", "Fire Spin", "Fissure", "Flail", "Flame Wheel",
		"Flamethrower", "Flare Blitz", "Flash", "Flash Cannon", "Flatter",
		"Fling", "Fly", "Focus Blast", "Focus Energy", "Focus Punch",
		"Follow Me", "Force Palm", "Foresight", "Frenzy Plant", "Frustration",
		"Fury Attack", "Fury Cutter", "Fury Swipes", "Future Sight", "Gastro Acid",
		"Giga Drain", "Giga Impact", "Glare", "Grass Knot", "GrassWhistle",
		"Gravity", "Growl", "Growth", "Grudge", "Guard Swap",
		"Guillotine", "Gunk Shot", "Gust", "Gyro Ball", "Hail",
		"Hammer Arm", "Harden", "Haze", "Head Smash", "Headbutt",
		"Heal Bell", "Heal Block", "Heal Order", "Healing Wish", "Heart Swap",
		"Heat Wave", "Helping Hand", "Hi Jump Kick", "Hidden Power", "Horn Attack",
		"Horn Drill", "Howl", "Hydro Cannon", "Hydro Pump", "Hyper Beam",
		"Hyper Fang", "Hyper Voice", "Hypnosis", "Ice Ball", "Ice Beam",
		"Ice Fang", "Ice Punch", "Ice Shard", "Icicle Spear", "Icy Wind",
		"Imprison", "Ingrain", "Iron Defense", "Iron Head", "Iron Tail",
		"Judgment", "Jump Kick", "Karate Chop", "Kinesis", "Knock Off",
		"Last Resort", "Lava Plume", "Leaf Blade", "Leaf Storm", "Leech Life",
		"Leech Seed", "Leer", "Lick", "Light Screen", "Lock-On",
		"Lovely Kiss", "Low Kick", "Lucky Chant", "Lunar Dance", "Luster Purge",
		"Mach Punch", "Magic Coat", "Magical Leaf", "Magma Storm", "Magnet Bomb",
		"Magnet Rise", "Magnitude", "Me First", "Mean Look", "Meditate",
		"Mega Drain", "Mega Kick", "Mega Punch", "Megahorn", "Memento",
		"Metal Burst", "Metal Claw", "Metal Sound", "Meteor Mash", "Metronome",
		"Milk Drink", "Mimic", "Mind Reader", "Minimize", "Miracle Eye",
		"Mirror Coat", "Mirror Move", "Mirror Shot", "Mist", "Mist Ball",
		"Moonlight", "Morning Sun", "Mud Bomb", "Mud Shot", "Mud Sport",
		"Mud-Slap", "Muddy Water", "Nasty Plot", "Natural Gift", "Nature Power",
		"Needle Arm", "Night Shade", "Night Slash", "Nightmare", "Octazooka",
		"Odor Sleuth", "Ominous Wind", "Outrage", "Overheat", "Pain Split",
		"Pay Day", "Payback", "Peck", "Perish Song", "Petal Dance",
		"Pin Missile", "Pluck", "Poison Fang", "Poison Gas", "Poison Jab",
		"Poison Sting", "Poison Tail", "PoisonPowder", "Pound", "Powder Snow",
		"Power Gem", "Power Swap", "Power Trick", "Power Whip", "Present",
		"Protect", "Psybeam", "Psych Up", "Psychic", "Psycho Boost",
		"Psycho Cut", "Psycho Shift", "Psywave", "Punishment", "Pursuit",
		"Quick Attack", "Rage", "Rain Dance", "Rapid Spin", "Razor Leaf",
		"Razor Wind", "Recover", "Recycle", "Reflect", "Refresh",
		"Rest", "Return", "Revenge", "Reversal", "Roar",
		"Roar Of Time", "Rock Blast", "Rock Climb", "Rock Polish", "Rock Slide",
		"Rock Smash", "Rock Throw", "Rock Tomb", "Rock Wrecker", "Role Play",
		"Rolling Kick", "Rollout", "Roost", "Sacred Fire", "Safeguard",
		"Sand Tomb", "Sand-Attack", "Sandstorm", "Scary Face", "Scratch", "Screech",
		"Secret Power", "Seed Bomb", "Seed Flare", "Seismic Toss", "Selfdestruct", "Shadow Ball",
		"Shadow Claw", "Shadow Force", "Shadow Punch", "Shadow Sneak", "Sharpen", "Sheer Cold",
		"Shock Wave", "Signal Beam", "Silver Wind", "Sing", "Sketch", "Skill Swap",
		"Skull Bash", "Sky Attack", "Sky Uppercut", "Slack Off", "Slam", "Slash",
		"Sleep Powder", "Sleep Talk", "Sludge", "Sludge Bomb", "SmellingSalt",
		"Smog", "SmokeScreen", "Snatch", "Snore", "Softboiled",
		"SolarBeam", "SonicBoom", "Spacial Rend", "Spark", "Spider Web",
		"Spike Cannon", "Spikes", "Spit Up", "Spite", "Splash",
		"Spore", "Stealth Rock", "Steel Wing", "Stockpile", "Stomp",
		"Stone Edge", "Strength", "String Shot", "Struggle", "Stun Spore",
		"Submission", "Substitute", "Sucker Punch", "Sunny Day", "Super Fang",
		"Superpower", "Supersonic", "Surf", "Swagger", "Swallow",
		"Sweet Kiss", "Sweet Scent", "Swift", "Switch0", "Switch1",
		"Switch2", "Switch3", "Switch4", "Switch5", "Switcheroo",
		"Swords Dance", "Synthesis", "Tackle", "Tail Glow", "Tail Whip",
		"Tailwind", "Take Down", "Taunt", "Teeter Dance", "Teleport",
		"Thief", "Thrash", "Thunder", "Thunder Fang", "Thunder Wave",
		"Thunderbolt", "ThunderPunch", "ThunderShock", "Tickle", "Torment",
		"Toxic", "Toxic Spikes", "Transform", "Tri Attack", "Trick",
		"Trick Room", "Triple Kick", "Trump Card", "Twineedle", "Twister",
		"U-turn", "Uproar", "Vacuum Wave", "ViceGrip", "Vine Whip",
		"Vital Throw", "Volt Tackle", "Wake-Up Slap", "Water Gun", "Water Pulse",
		"Water Sport", "Water Spout", "Waterfall", "Weather Ball", "Whirlpool",
		"Whirlwind", "Will-O-Wisp", "Wing Attack", "Wish", "Withdraw",
		"Wood Hammer", "Worry Seed", "Wrap", "Wring Out", "X-Scissor",
		"Yawn", "Zap Cannon", "Zen Headbutt", "END_MOVE"
	};
	return name_to_string [name];
}

std::string Move::to_string() const {
	return to_string (name);
}

Move::Moves Move::from_string (std::string const & str) {
	static std::map <std::string, Moves> const converter {
		{ "Absorb", ABSORB },
		{ "Acid", ACID },
		{ "Acid Armor", ACID_ARMOR },
		{ "Acupressure", ACUPRESSURE },
		{ "Aerial Ace", AERIAL_ACE },
		{ "Aeroblast", AEROBLAST },
		{ "Agility", AGILITY },
		{ "Air Cutter", AIR_CUTTER },
		{ "Air Slash", AIR_SLASH },
		{ "Amnesia", AMNESIA },
		{ "AncientPower", ANCIENTPOWER },
		{ "Ancientpower", ANCIENTPOWER },
		{ "Aqua Jet", AQUA_JET },
		{ "Aqua Ring", AQUA_RING },
		{ "Aqua Tail", AQUA_TAIL },
		{ "Arm Thrust", ARM_THRUST },
		{ "Aromatherapy", AROMATHERAPY },
		{ "Assist", ASSIST },
		{ "Assurance", ASSURANCE },
		{ "Astonish", ASTONISH },
		{ "Attack Order", ATTACK_ORDER },
		{ "Attract", ATTRACT },
		{ "Aura Sphere", AURA_SPHERE },
		{ "Aurora Beam", AURORA_BEAM },
		{ "Avalanche", AVALANCHE },
		{ "Barrage", BARRAGE },
		{ "Barrier", BARRIER },
		{ "Baton Pass", BATON_PASS },
		{ "Beat Up", BEAT_UP },
		{ "Belly Drum", BELLY_DRUM },
		{ "Bide", BIDE },
		{ "Bind", BIND },
		{ "Bite", BITE },
		{ "Blast Burn", BLAST_BURN },
		{ "Blaze Kick", BLAZE_KICK },
		{ "Blizzard", BLIZZARD },
		{ "Block", BLOCK },
		{ "Body Slam", BODY_SLAM },
		{ "Bone Club", BONE_CLUB },
		{ "Bone Rush", BONE_RUSH },
		{ "Bonemerang", BONEMERANG },
		{ "Bounce", BOUNCE },
		{ "Brave Bird", BRAVE_BIRD },
		{ "Brick Break", BRICK_BREAK },
		{ "Brine", BRINE },
		{ "Bubble", BUBBLE },
		{ "BubbleBeam", BUBBLEBEAM },
		{ "Bubblebeam", BUBBLEBEAM },
		{ "Bug Bite", BUG_BITE },
		{ "Bug Buzz", BUG_BUZZ },
		{ "Bulk Up", BULK_UP },
		{ "Bullet Punch", BULLET_PUNCH },
		{ "Bullet Seed", BULLET_SEED },
		{ "Calm Mind", CALM_MIND },
		{ "Camouflage", CAMOUFLAGE },
		{ "Captivate", CAPTIVATE },
		{ "Charge", CHARGE },
		{ "Charge Beam", CHARGE_BEAM },
		{ "Charm", CHARM },
		{ "Chatter", CHATTER },
		{ "Clamp", CLAMP },
		{ "Close Combat", CLOSE_COMBAT },
		{ "Comet Punch", COMET_PUNCH },
		{ "Confuse Ray", CONFUSE_RAY },
		{ "Confusion", CONFUSION },
		{ "Constrict", CONSTRICT },
		{ "Conversion", CONVERSION },
		{ "Conversion2", CONVERSION2 },
		{ "Conversion 2", CONVERSION2 },
		{ "Copycat", COPYCAT },
		{ "Cosmic Power", COSMIC_POWER },
		{ "Cotton Spore", COTTON_SPORE },
		{ "Counter", COUNTER },
		{ "Covet", COVET },
		{ "Crabhammer", CRABHAMMER },
		{ "Cross Chop", CROSS_CHOP },
		{ "Cross Poison", CROSS_POISON },
		{ "Crunch", CRUNCH },
		{ "Crush Claw", CRUSH_CLAW },
		{ "Crush Grip", CRUSH_GRIP },
		{ "Curse", CURSE },
		{ "Cut", CUT },
		{ "Dark Pulse", DARK_PULSE },
		{ "Dark Void", DARK_VOID },
		{ "Defend Order", DEFEND_ORDER },
		{ "Defense Curl", DEFENSE_CURL },
		{ "Defog", DEFOG },
		{ "Destiny Bond", DESTINY_BOND },
		{ "Detect", DETECT },
		{ "Dig", DIG },
		{ "Disable", DISABLE },
		{ "Discharge", DISCHARGE },
		{ "Dive", DIVE },
		{ "Dizzy Punch", DIZZY_PUNCH },
		{ "Doom Desire", DOOM_DESIRE },
		{ "Double Hit", DOUBLE_HIT },
		{ "Double Kick", DOUBLE_KICK },
		{ "Double Team", DOUBLE_TEAM },
		{ "Double-Edge", DOUBLE_EDGE },
		{ "Double-edge", DOUBLE_EDGE },
		{ "DoubleSlap", DOUBLESLAP },
		{ "Doubleslap", DOUBLESLAP },
		{ "Draco Meteor", DRACO_METEOR },
		{ "Dragon Claw", DRAGON_CLAW },
		{ "Dragon Dance", DRAGON_DANCE },
		{ "Dragon Pulse", DRAGON_PULSE },
		{ "Dragon Rage", DRAGON_RAGE },
		{ "Dragon Rush", DRAGON_RUSH },
		{ "DragonBreath", DRAGONBREATH },
		{ "Dragonbreath", DRAGONBREATH },
		{ "Drain Punch", DRAIN_PUNCH },
		{ "Dream Eater", DREAM_EATER },
		{ "Drill Peck", DRILL_PECK },
		{ "DynamicPunch", DYNAMICPUNCH },
		{ "Dynamicpunch", DYNAMICPUNCH },
		{ "Earth Power", EARTH_POWER },
		{ "Earthquake", EARTHQUAKE },
		{ "Egg Bomb", EGG_BOMB },
		{ "Embargo", EMBARGO },
		{ "Ember", EMBER },
		{ "Encore", ENCORE },
		{ "Endeavor", ENDEAVOR },
		{ "Endure", ENDURE },
		{ "Energy Ball", ENERGY_BALL },
		{ "Eruption", ERUPTION },
		{ "Explosion", EXPLOSION },
		{ "Extrasensory", EXTRASENSORY },
		{ "ExtremeSpeed", EXTREMESPEED },
		{ "Extremespeed", EXTREMESPEED },
		{ "Facade", FACADE },
		{ "Faint Attack", FAINT_ATTACK },
		{ "Fake Out", FAKE_OUT },
		{ "Fake Tears", FAKE_TEARS },
		{ "False Swipe", FALSE_SWIPE },
		{ "FeatherDance", FEATHERDANCE },
		{ "Featherdance", FEATHERDANCE },
		{ "Feint", FEINT },
		{ "Fire Blast", FIRE_BLAST },
		{ "Fire Fang", FIRE_FANG },
		{ "Fire Punch", FIRE_PUNCH },
		{ "Fire Spin", FIRE_SPIN },
		{ "Fissure", FISSURE },
		{ "Flail", FLAIL },
		{ "Flame Wheel", FLAME_WHEEL },
		{ "Flamethrower", FLAMETHROWER },
		{ "Flare Blitz", FLARE_BLITZ },
		{ "Flash", FLASH },
		{ "Flash Cannon", FLASH_CANNON },
		{ "Flatter", FLATTER },
		{ "Fling", FLING },
		{ "Fly", FLY },
		{ "Focus Blast", FOCUS_BLAST },
		{ "Focus Energy", FOCUS_ENERGY },
		{ "Focus Punch", FOCUS_PUNCH },
		{ "Follow Me", FOLLOW_ME },
		{ "Force Palm", FORCE_PALM },
		{ "Foresight", FORESIGHT },
		{ "Frenzy Plant", FRENZY_PLANT },
		{ "Frustration", FRUSTRATION },
		{ "Fury Attack", FURY_ATTACK },
		{ "Fury Cutter", FURY_CUTTER },
		{ "Fury Swipes", FURY_SWIPES },
		{ "Future Sight", FUTURE_SIGHT },
		{ "Gastro Acid", GASTRO_ACID },
		{ "Giga Drain", GIGA_DRAIN },
		{ "Giga Impact", GIGA_IMPACT },
		{ "Glare", GLARE },
		{ "Grass Knot", GRASS_KNOT },
		{ "GrassWhistle", GRASSWHISTLE },
		{ "Grasswhistle", GRASSWHISTLE },
		{ "Gravity", GRAVITY },
		{ "Growl", GROWL },
		{ "Growth", GROWTH },
		{ "Grudge", GRUDGE },
		{ "Guard Swap", GUARD_SWAP },
		{ "Guillotine", GUILLOTINE },
		{ "Gunk Shot", GUNK_SHOT },
		{ "Gust", GUST },
		{ "Gyro Ball", GYRO_BALL },
		{ "Hail", HAIL },
		{ "Hammer Arm", HAMMER_ARM },
		{ "Harden", HARDEN },
		{ "Haze", HAZE },
		{ "Head Smash", HEAD_SMASH },
		{ "Headbutt", HEADBUTT },
		{ "Heal Bell", HEAL_BELL },
		{ "Heal Block", HEAL_BLOCK },
		{ "Heal Order", HEAL_ORDER },
		{ "Healing Wish", HEALING_WISH },
		{ "Heart Swap", HEART_SWAP },
		{ "Heat Wave", HEAT_WAVE },
		{ "Helping Hand", HELPING_HAND },
		{ "Hi Jump Kick", HI_JUMP_KICK },
		{ "Hidden Power", HIDDEN_POWER },
		{ "Hidden Power Bug", HIDDEN_POWER },
		{ "Hidden Power Dark", HIDDEN_POWER },
		{ "Hidden Power Dragon", HIDDEN_POWER },
		{ "Hidden Power Electric", HIDDEN_POWER },
		{ "Hidden Power Fighting", HIDDEN_POWER },
		{ "Hidden Power Fire", HIDDEN_POWER },
		{ "Hidden Power Flying", HIDDEN_POWER },
		{ "Hidden Power Ghost", HIDDEN_POWER },
		{ "Hidden Power Grass", HIDDEN_POWER },
		{ "Hidden Power Ground", HIDDEN_POWER },
		{ "Hidden Power Ice", HIDDEN_POWER },
		{ "Hidden Power Poison", HIDDEN_POWER },
		{ "Hidden Power Psychic", HIDDEN_POWER },
		{ "Hidden Power Rock", HIDDEN_POWER },
		{ "Hidden Power Steel", HIDDEN_POWER },
		{ "Hidden Power Water", HIDDEN_POWER },
		{ "Horn Attack", HORN_ATTACK },
		{ "Horn Drill", HORN_DRILL },
		{ "Howl", HOWL },
		{ "Hydro Cannon", HYDRO_CANNON },
		{ "Hydro Pump", HYDRO_PUMP },
		{ "Hyper Beam", HYPER_BEAM },
		{ "Hyper Fang", HYPER_FANG },
		{ "Hyper Voice", HYPER_VOICE },
		{ "Hypnosis", HYPNOSIS },
		{ "Ice Ball", ICE_BALL },
		{ "Ice Beam", ICE_BEAM },
		{ "Ice Fang", ICE_FANG },
		{ "Ice Punch", ICE_PUNCH },
		{ "Ice Shard", ICE_SHARD },
		{ "Icicle Spear", ICICLE_SPEAR },
		{ "Icy Wind", ICY_WIND },
		{ "Imprison", IMPRISON },
		{ "Ingrain", INGRAIN },
		{ "Iron Defense", IRON_DEFENSE },
		{ "Iron Head", IRON_HEAD },
		{ "Iron Tail", IRON_TAIL },
		{ "Judgment", JUDGMENT },
		{ "Jump Kick", JUMP_KICK },
		{ "Karate Chop", KARATE_CHOP },
		{ "Kinesis", KINESIS },
		{ "Knock Off", KNOCK_OFF },
		{ "Last Resort", LAST_RESORT },
		{ "Lava Plume", LAVA_PLUME },
		{ "Leaf Blade", LEAF_BLADE },
		{ "Leaf Storm", LEAF_STORM },
		{ "Leech Life", LEECH_LIFE },
		{ "Leech Seed", LEECH_SEED },
		{ "Leer", LEER },
		{ "Lick", LICK },
		{ "Light Screen", LIGHT_SCREEN },
		{ "Lock-On", LOCK_ON },
		{ "Lock-on", LOCK_ON },
		{ "Lovely Kiss", LOVELY_KISS },
		{ "Low Kick", LOW_KICK },
		{ "Lucky Chant", LUCKY_CHANT },
		{ "Lunar Dance", LUNAR_DANCE },
		{ "Luster Purge", LUSTER_PURGE },
		{ "Mach Punch", MACH_PUNCH },
		{ "Magic Coat", MAGIC_COAT },
		{ "Magical Leaf", MAGICAL_LEAF },
		{ "Magma Storm", MAGMA_STORM },
		{ "Magnet Bomb", MAGNET_BOMB },
		{ "Magnet Rise", MAGNET_RISE },
		{ "Magnitude", MAGNITUDE },
		{ "Me First", ME_FIRST },
		{ "Mean Look", MEAN_LOOK },
		{ "Meditate", MEDITATE },
		{ "Mega Drain", MEGA_DRAIN },
		{ "Mega Kick", MEGA_KICK },
		{ "Mega Punch", MEGA_PUNCH },
		{ "Megahorn", MEGAHORN },
		{ "Memento", MEMENTO },
		{ "Metal Burst", METAL_BURST },
		{ "Metal Claw", METAL_CLAW },
		{ "Metal Sound", METAL_SOUND },
		{ "Meteor Mash", METEOR_MASH },
		{ "Metronome", METRONOME },
		{ "Milk Drink", MILK_DRINK },
		{ "Mimic", MIMIC },
		{ "Mind Reader", MIND_READER },
		{ "Minimize", MINIMIZE },
		{ "Miracle Eye", MIRACLE_EYE },
		{ "Mirror Coat", MIRROR_COAT },
		{ "Mirror Move", MIRROR_MOVE },
		{ "Mirror Shot", MIRROR_SHOT },
		{ "Mist", MIST },
		{ "Mist Ball", MIST_BALL },
		{ "Moonlight", MOONLIGHT },
		{ "Morning Sun", MORNING_SUN },
		{ "Mud Bomb", MUD_BOMB },
		{ "Mud Shot", MUD_SHOT },
		{ "Mud Sport", MUD_SPORT },
		{ "Mud-Slap", MUD_SLAP },
		{ "Mud-slap", MUD_SLAP },
		{ "Muddy Water", MUDDY_WATER },
		{ "Nasty Plot", NASTY_PLOT },
		{ "Natural Gift", NATURAL_GIFT },
		{ "Nature Power", NATURE_POWER },
		{ "Needle Arm", NEEDLE_ARM },
		{ "Night Shade", NIGHT_SHADE },
		{ "Night Slash", NIGHT_SLASH },
		{ "Nightmare", NIGHTMARE },
		{ "Octazooka", OCTAZOOKA },
		{ "Odor Sleuth", ODOR_SLEUTH },
		{ "Ominous Wind", OMINOUS_WIND },
		{ "Outrage", OUTRAGE },
		{ "Overheat", OVERHEAT },
		{ "Pain Split", PAIN_SPLIT },
		{ "Pay Day", PAY_DAY },
		{ "Payback", PAYBACK },
		{ "Peck", PECK },
		{ "Perish Song", PERISH_SONG },
		{ "Petal Dance", PETAL_DANCE },
		{ "Pin Missile", PIN_MISSILE },
		{ "Pluck", PLUCK },
		{ "Poison Fang", POISON_FANG },
		{ "Poison Gas", POISON_GAS },
		{ "Poison Jab", POISON_JAB },
		{ "Poison Sting", POISON_STING },
		{ "Poison Tail", POISON_TAIL },
		{ "PoisonPowder", POISONPOWDER },
		{ "Poisonpowder", POISONPOWDER },
		{ "Pound", POUND },
		{ "Powder Snow", POWDER_SNOW },
		{ "Power Gem", POWER_GEM },
		{ "Power Swap", POWER_SWAP },
		{ "Power Trick", POWER_TRICK },
		{ "Power Whip", POWER_WHIP },
		{ "Present", PRESENT },
		{ "Protect", PROTECT },
		{ "Psybeam", PSYBEAM },
		{ "Psych Up", PSYCH_UP },
		{ "Psychic", PSYCHIC },
		{ "Psycho Boost", PSYCHO_BOOST },
		{ "Psycho Cut", PSYCHO_CUT },
		{ "Psycho Shift", PSYCHO_SHIFT },
		{ "Psywave", PSYWAVE },
		{ "Punishment", PUNISHMENT },
		{ "Pursuit", PURSUIT },
		{ "Quick Attack", QUICK_ATTACK },
		{ "Rage", RAGE },
		{ "Rain Dance", RAIN_DANCE },
		{ "Rapid Spin", RAPID_SPIN },
		{ "Razor Leaf", RAZOR_LEAF },
		{ "Razor Wind", RAZOR_WIND },
		{ "Recover", RECOVER },
		{ "Recycle", RECYCLE },
		{ "Reflect", REFLECT },
		{ "Refresh", REFRESH },
		{ "Rest", REST },
		{ "Return", RETURN },
		{ "Revenge", REVENGE },
		{ "Reversal", REVERSAL },
		{ "Roar", ROAR },
		{ "Roar Of Time", ROAR_OF_TIME },
		{ "Rock Blast", ROCK_BLAST },
		{ "Rock Climb", ROCK_CLIMB },
		{ "Rock Polish", ROCK_POLISH },
		{ "Rock Slide", ROCK_SLIDE },
		{ "Rock Smash", ROCK_SMASH },
		{ "Rock Throw", ROCK_THROW },
		{ "Rock Tomb", ROCK_TOMB },
		{ "Rock Wrecker", ROCK_WRECKER },
		{ "Role Play", ROLE_PLAY },
		{ "Rolling Kick", ROLLING_KICK },
		{ "Rollout", ROLLOUT },
		{ "Roost", ROOST },
		{ "Sacred Fire", SACRED_FIRE },
		{ "Safeguard", SAFEGUARD },
		{ "Sand Tomb", SAND_TOMB },
		{ "Sand-Attack", SAND_ATTACK },
		{ "Sand-attack", SAND_ATTACK },
		{ "Sandstorm", SANDSTORM },
		{ "Scary Face", SCARY_FACE },
		{ "Scratch", SCRATCH },
		{ "Screech", SCREECH },
		{ "Secret Power", SECRET_POWER },
		{ "Seed Bomb", SEED_BOMB },
		{ "Seed Flare", SEED_FLARE },
		{ "Seismic Toss", SEISMIC_TOSS },
		{ "Selfdestruct", SELFDESTRUCT },
		{ "Shadow Ball", SHADOW_BALL },
		{ "Shadow Claw", SHADOW_CLAW },
		{ "Shadow Force", SHADOW_FORCE },
		{ "Shadow Punch", SHADOW_PUNCH },
		{ "Shadow Sneak", SHADOW_SNEAK },
		{ "Sharpen", SHARPEN },
		{ "Sheer Cold", SHEER_COLD },
		{ "Shock Wave", SHOCK_WAVE },
		{ "Signal Beam", SIGNAL_BEAM },
		{ "Silver Wind", SILVER_WIND },
		{ "Sing", SING },
		{ "Sketch", SKETCH },
		{ "Skill Swap", SKILL_SWAP },
		{ "Skull Bash", SKULL_BASH },
		{ "Sky Attack", SKY_ATTACK },
		{ "Sky Uppercut", SKY_UPPERCUT },
		{ "Slack Off", SLACK_OFF },
		{ "Slam", SLAM },
		{ "Slash", SLASH },
		{ "Sleep Powder", SLEEP_POWDER },
		{ "Sleep Talk", SLEEP_TALK },
		{ "Sludge", SLUDGE },
		{ "Sludge Bomb", SLUDGE_BOMB },
		{ "SmellingSalt", SMELLINGSALT },
		{ "Smellingsalt", SMELLINGSALT },
		{ "Smog", SMOG },
		{ "SmokeScreen", SMOKESCREEN },
		{ "Smokescreen", SMOKESCREEN },
		{ "Snatch", SNATCH },
		{ "Snore", SNORE },
		{ "Softboiled", SOFTBOILED },
		{ "SolarBeam", SOLARBEAM },
		{ "Solarbeam", SOLARBEAM },
		{ "SonicBoom", SONICBOOM },
		{ "Sonicboom", SONICBOOM },
		{ "Spacial Rend", SPACIAL_REND },
		{ "Spark", SPARK },
		{ "Spider Web", SPIDER_WEB },
		{ "Spike Cannon", SPIKE_CANNON },
		{ "Spikes", SPIKES },
		{ "Spit Up", SPIT_UP },
		{ "Spite", SPITE },
		{ "Splash", SPLASH },
		{ "Spore", SPORE },
		{ "Stealth Rock", STEALTH_ROCK },
		{ "Steel Wing", STEEL_WING },
		{ "Stockpile", STOCKPILE },
		{ "Stomp", STOMP },
		{ "Stone Edge", STONE_EDGE },
		{ "Strength", STRENGTH },
		{ "String Shot", STRING_SHOT },
		{ "Struggle", STRUGGLE },
		{ "Stun Spore", STUN_SPORE },
		{ "Submission", SUBMISSION },
		{ "Substitute", SUBSTITUTE },
		{ "Sucker Punch", SUCKER_PUNCH },
		{ "Sunny Day", SUNNY_DAY },
		{ "Super Fang", SUPER_FANG },
		{ "Superpower", SUPERPOWER },
		{ "Supersonic", SUPERSONIC },
		{ "Surf", SURF },
		{ "Swagger", SWAGGER },
		{ "Swallow", SWALLOW },
		{ "Sweet Kiss", SWEET_KISS },
		{ "Sweet Scent", SWEET_SCENT },
		{ "Swift", SWIFT },
		{ "Switch0", SWITCH0 },
		{ "Switch1", SWITCH1 },
		{ "Switch2", SWITCH2 },
		{ "Switch3", SWITCH3 },
		{ "Switch4", SWITCH4 },
		{ "Switch5", SWITCH5 },
		{ "Switcheroo", SWITCHEROO },
		{ "Swords Dance", SWORDS_DANCE },
		{ "Synthesis", SYNTHESIS },
		{ "Tackle", TACKLE },
		{ "Tail Glow", TAIL_GLOW },
		{ "Tail Whip", TAIL_WHIP },
		{ "Tailwind", TAILWIND },
		{ "Take Down", TAKE_DOWN },
		{ "Taunt", TAUNT },
		{ "Teeter Dance", TEETER_DANCE },
		{ "Teleport", TELEPORT },
		{ "Thief", THIEF },
		{ "Thrash", THRASH },
		{ "Thunder", THUNDER },
		{ "Thunder Fang", THUNDER_FANG },
		{ "Thunder Wave", THUNDER_WAVE },
		{ "Thunderbolt", THUNDERBOLT },
		{ "ThunderPunch", THUNDERPUNCH },
		{ "Thunderpunch", THUNDERPUNCH },
		{ "ThunderShock", THUNDERSHOCK },
		{ "Thundershock", THUNDERSHOCK },
		{ "Tickle", TICKLE },
		{ "Torment", TORMENT },
		{ "Toxic", TOXIC },
		{ "Toxic Spikes", TOXIC_SPIKES },
		{ "Transform", TRANSFORM },
		{ "Tri Attack", TRI_ATTACK },
		{ "Trick", TRICK },
		{ "Trick Room", TRICK_ROOM },
		{ "Triple Kick", TRIPLE_KICK },
		{ "Trump Card", TRUMP_CARD },
		{ "Twineedle", TWINEEDLE },
		{ "Twister", TWISTER },
		{ "U-turn", U_TURN },
		{ "Uproar", UPROAR },
		{ "Vacuum Wave", VACUUM_WAVE },
		{ "ViceGrip", VICEGRIP },
		{ "Vicegrip", VICEGRIP },
		{ "Vine Whip", VINE_WHIP },
		{ "Vital Throw", VITAL_THROW },
		{ "Volt Tackle", VOLT_TACKLE },
		{ "Wake-Up Slap", WAKE_UP_SLAP },
		{ "Wake-up Slap", WAKE_UP_SLAP },
		{ "Water Gun", WATER_GUN },
		{ "Water Pulse", WATER_PULSE },
		{ "Water Sport", WATER_SPORT },
		{ "Water Spout", WATER_SPOUT },
		{ "Waterfall", WATERFALL },
		{ "Weather Ball", WEATHER_BALL },
		{ "Whirlpool", WHIRLPOOL },
		{ "Whirlwind", WHIRLWIND },
		{ "Will-O-Wisp", WILL_O_WISP },
		{ "Will-o-Wisp", WILL_O_WISP },
		{ "Will-o-wisp", WILL_O_WISP },
		{ "Wing Attack", WING_ATTACK },
		{ "Wish", WISH },
		{ "Withdraw", WITHDRAW },
		{ "Wood Hammer", WOOD_HAMMER },
		{ "Worry Seed", WORRY_SEED },
		{ "Wrap", WRAP },
		{ "Wring Out", WRING_OUT },
		{ "X-Scissor", X_SCISSOR },
		{ "X-scissor", X_SCISSOR },
		{ "Yawn", YAWN },
		{ "Zap Cannon", ZAP_CANNON },
		{ "Zen Headbutt", ZEN_HEADBUTT },
		{ "END_MOVE", END }
	};
	auto const it = converter.find (str);
	if (it != converter.end ())
		return it->second;
	else
		throw InvalidFromStringConversion ("Move", str);
}

}	// namespace technicalmachine
