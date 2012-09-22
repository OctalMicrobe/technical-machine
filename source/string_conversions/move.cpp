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

#include "conversion.hpp"

#include <cassert>
#include <map>
#include <string>

#include "invalid_string_conversion.hpp"

#include "../move/move.hpp"
#include "../move/moves.hpp"

namespace technicalmachine {

template<>
std::string to_string(Moves const name) {
	assert(name <= Moves::END);
	static std::string const name_to_string [] = {
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
	return name_to_string[static_cast<unsigned>(name)];
}

template<>
Moves from_string(std::string const & str) {
	static std::map<std::string, Moves> const converter {
		{ "Absorb", Moves::ABSORB },
		{ "Acid", Moves::ACID },
		{ "Acid Armor", Moves::ACID_ARMOR },
		{ "Acupressure", Moves::ACUPRESSURE },
		{ "Aerial Ace", Moves::AERIAL_ACE },
		{ "Aeroblast", Moves::AEROBLAST },
		{ "Agility", Moves::AGILITY },
		{ "Air Cutter", Moves::AIR_CUTTER },
		{ "Air Slash", Moves::AIR_SLASH },
		{ "Amnesia", Moves::AMNESIA },
		{ "AncientPower", Moves::ANCIENTPOWER },
		{ "Ancientpower", Moves::ANCIENTPOWER },
		{ "Aqua Jet", Moves::AQUA_JET },
		{ "Aqua Ring", Moves::AQUA_RING },
		{ "Aqua Tail", Moves::AQUA_TAIL },
		{ "Arm Thrust", Moves::ARM_THRUST },
		{ "Aromatherapy", Moves::AROMATHERAPY },
		{ "Assist", Moves::ASSIST },
		{ "Assurance", Moves::ASSURANCE },
		{ "Astonish", Moves::ASTONISH },
		{ "Attack Order", Moves::ATTACK_ORDER },
		{ "Attract", Moves::ATTRACT },
		{ "Aura Sphere", Moves::AURA_SPHERE },
		{ "Aurora Beam", Moves::AURORA_BEAM },
		{ "Avalanche", Moves::AVALANCHE },
		{ "Barrage", Moves::BARRAGE },
		{ "Barrier", Moves::BARRIER },
		{ "Baton Pass", Moves::BATON_PASS },
		{ "Beat Up", Moves::BEAT_UP },
		{ "Belly Drum", Moves::BELLY_DRUM },
		{ "Bide", Moves::BIDE },
		{ "Bind", Moves::BIND },
		{ "Bite", Moves::BITE },
		{ "Blast Burn", Moves::BLAST_BURN },
		{ "Blaze Kick", Moves::BLAZE_KICK },
		{ "Blizzard", Moves::BLIZZARD },
		{ "Block", Moves::BLOCK },
		{ "Body Slam", Moves::BODY_SLAM },
		{ "Bone Club", Moves::BONE_CLUB },
		{ "Bone Rush", Moves::BONE_RUSH },
		{ "Bonemerang", Moves::BONEMERANG },
		{ "Bounce", Moves::BOUNCE },
		{ "Brave Bird", Moves::BRAVE_BIRD },
		{ "Brick Break", Moves::BRICK_BREAK },
		{ "Brine", Moves::BRINE },
		{ "Bubble", Moves::BUBBLE },
		{ "BubbleBeam", Moves::BUBBLEBEAM },
		{ "Bubblebeam", Moves::BUBBLEBEAM },
		{ "Bug Bite", Moves::BUG_BITE },
		{ "Bug Buzz", Moves::BUG_BUZZ },
		{ "Bulk Up", Moves::BULK_UP },
		{ "Bullet Punch", Moves::BULLET_PUNCH },
		{ "Bullet Seed", Moves::BULLET_SEED },
		{ "Calm Mind", Moves::CALM_MIND },
		{ "Camouflage", Moves::CAMOUFLAGE },
		{ "Captivate", Moves::CAPTIVATE },
		{ "Charge", Moves::CHARGE },
		{ "Charge Beam", Moves::CHARGE_BEAM },
		{ "Charm", Moves::CHARM },
		{ "Chatter", Moves::CHATTER },
		{ "Clamp", Moves::CLAMP },
		{ "Close Combat", Moves::CLOSE_COMBAT },
		{ "Comet Punch", Moves::COMET_PUNCH },
		{ "Confuse Ray", Moves::CONFUSE_RAY },
		{ "Confusion", Moves::CONFUSION },
		{ "Constrict", Moves::CONSTRICT },
		{ "Conversion", Moves::CONVERSION },
		{ "Conversion2", Moves::CONVERSION2 },
		{ "Conversion 2", Moves::CONVERSION2 },
		{ "Copycat", Moves::COPYCAT },
		{ "Cosmic Power", Moves::COSMIC_POWER },
		{ "Cotton Spore", Moves::COTTON_SPORE },
		{ "Counter", Moves::COUNTER },
		{ "Covet", Moves::COVET },
		{ "Crabhammer", Moves::CRABHAMMER },
		{ "Cross Chop", Moves::CROSS_CHOP },
		{ "Cross Poison", Moves::CROSS_POISON },
		{ "Crunch", Moves::CRUNCH },
		{ "Crush Claw", Moves::CRUSH_CLAW },
		{ "Crush Grip", Moves::CRUSH_GRIP },
		{ "Curse", Moves::CURSE },
		{ "Cut", Moves::CUT },
		{ "Dark Pulse", Moves::DARK_PULSE },
		{ "Dark Void", Moves::DARK_VOID },
		{ "Defend Order", Moves::DEFEND_ORDER },
		{ "Defense Curl", Moves::DEFENSE_CURL },
		{ "Defog", Moves::DEFOG },
		{ "Destiny Bond", Moves::DESTINY_BOND },
		{ "Detect", Moves::DETECT },
		{ "Dig", Moves::DIG },
		{ "Disable", Moves::DISABLE },
		{ "Discharge", Moves::DISCHARGE },
		{ "Dive", Moves::DIVE },
		{ "Dizzy Punch", Moves::DIZZY_PUNCH },
		{ "Doom Desire", Moves::DOOM_DESIRE },
		{ "Double Hit", Moves::DOUBLE_HIT },
		{ "Double Kick", Moves::DOUBLE_KICK },
		{ "Double Team", Moves::DOUBLE_TEAM },
		{ "Double-Edge", Moves::DOUBLE_EDGE },
		{ "Double-edge", Moves::DOUBLE_EDGE },
		{ "DoubleSlap", Moves::DOUBLESLAP },
		{ "Doubleslap", Moves::DOUBLESLAP },
		{ "Draco Meteor", Moves::DRACO_METEOR },
		{ "Dragon Claw", Moves::DRAGON_CLAW },
		{ "Dragon Dance", Moves::DRAGON_DANCE },
		{ "Dragon Pulse", Moves::DRAGON_PULSE },
		{ "Dragon Rage", Moves::DRAGON_RAGE },
		{ "Dragon Rush", Moves::DRAGON_RUSH },
		{ "DragonBreath", Moves::DRAGONBREATH },
		{ "Dragonbreath", Moves::DRAGONBREATH },
		{ "Drain Punch", Moves::DRAIN_PUNCH },
		{ "Dream Eater", Moves::DREAM_EATER },
		{ "Drill Peck", Moves::DRILL_PECK },
		{ "DynamicPunch", Moves::DYNAMICPUNCH },
		{ "Dynamicpunch", Moves::DYNAMICPUNCH },
		{ "Earth Power", Moves::EARTH_POWER },
		{ "Earthquake", Moves::EARTHQUAKE },
		{ "Egg Bomb", Moves::EGG_BOMB },
		{ "Embargo", Moves::EMBARGO },
		{ "Ember", Moves::EMBER },
		{ "Encore", Moves::ENCORE },
		{ "Endeavor", Moves::ENDEAVOR },
		{ "Endure", Moves::ENDURE },
		{ "Energy Ball", Moves::ENERGY_BALL },
		{ "Eruption", Moves::ERUPTION },
		{ "Explosion", Moves::EXPLOSION },
		{ "Extrasensory", Moves::EXTRASENSORY },
		{ "ExtremeSpeed", Moves::EXTREMESPEED },
		{ "Extremespeed", Moves::EXTREMESPEED },
		{ "Facade", Moves::FACADE },
		{ "Faint Attack", Moves::FAINT_ATTACK },
		{ "Fake Out", Moves::FAKE_OUT },
		{ "Fake Tears", Moves::FAKE_TEARS },
		{ "False Swipe", Moves::FALSE_SWIPE },
		{ "FeatherDance", Moves::FEATHERDANCE },
		{ "Featherdance", Moves::FEATHERDANCE },
		{ "Feint", Moves::FEINT },
		{ "Fire Blast", Moves::FIRE_BLAST },
		{ "Fire Fang", Moves::FIRE_FANG },
		{ "Fire Punch", Moves::FIRE_PUNCH },
		{ "Fire Spin", Moves::FIRE_SPIN },
		{ "Fissure", Moves::FISSURE },
		{ "Flail", Moves::FLAIL },
		{ "Flame Wheel", Moves::FLAME_WHEEL },
		{ "Flamethrower", Moves::FLAMETHROWER },
		{ "Flare Blitz", Moves::FLARE_BLITZ },
		{ "Flash", Moves::FLASH },
		{ "Flash Cannon", Moves::FLASH_CANNON },
		{ "Flatter", Moves::FLATTER },
		{ "Fling", Moves::FLING },
		{ "Fly", Moves::FLY },
		{ "Focus Blast", Moves::FOCUS_BLAST },
		{ "Focus Energy", Moves::FOCUS_ENERGY },
		{ "Focus Punch", Moves::FOCUS_PUNCH },
		{ "Follow Me", Moves::FOLLOW_ME },
		{ "Force Palm", Moves::FORCE_PALM },
		{ "Foresight", Moves::FORESIGHT },
		{ "Frenzy Plant", Moves::FRENZY_PLANT },
		{ "Frustration", Moves::FRUSTRATION },
		{ "Fury Attack", Moves::FURY_ATTACK },
		{ "Fury Cutter", Moves::FURY_CUTTER },
		{ "Fury Swipes", Moves::FURY_SWIPES },
		{ "Future Sight", Moves::FUTURE_SIGHT },
		{ "Gastro Acid", Moves::GASTRO_ACID },
		{ "Giga Drain", Moves::GIGA_DRAIN },
		{ "Giga Impact", Moves::GIGA_IMPACT },
		{ "Glare", Moves::GLARE },
		{ "Grass Knot", Moves::GRASS_KNOT },
		{ "GrassWhistle", Moves::GRASSWHISTLE },
		{ "Grasswhistle", Moves::GRASSWHISTLE },
		{ "Gravity", Moves::GRAVITY },
		{ "Growl", Moves::GROWL },
		{ "Growth", Moves::GROWTH },
		{ "Grudge", Moves::GRUDGE },
		{ "Guard Swap", Moves::GUARD_SWAP },
		{ "Guillotine", Moves::GUILLOTINE },
		{ "Gunk Shot", Moves::GUNK_SHOT },
		{ "Gust", Moves::GUST },
		{ "Gyro Ball", Moves::GYRO_BALL },
		{ "Hail", Moves::HAIL },
		{ "Hammer Arm", Moves::HAMMER_ARM },
		{ "Harden", Moves::HARDEN },
		{ "Haze", Moves::HAZE },
		{ "Head Smash", Moves::HEAD_SMASH },
		{ "Headbutt", Moves::HEADBUTT },
		{ "Heal Bell", Moves::HEAL_BELL },
		{ "Heal Block", Moves::HEAL_BLOCK },
		{ "Heal Order", Moves::HEAL_ORDER },
		{ "Healing Wish", Moves::HEALING_WISH },
		{ "Heart Swap", Moves::HEART_SWAP },
		{ "Heat Wave", Moves::HEAT_WAVE },
		{ "Helping Hand", Moves::HELPING_HAND },
		{ "Hi Jump Kick", Moves::HI_JUMP_KICK },
		{ "Hidden Power", Moves::HIDDEN_POWER },
		{ "Hidden Power Bug", Moves::HIDDEN_POWER },
		{ "Hidden Power Dark", Moves::HIDDEN_POWER },
		{ "Hidden Power Dragon", Moves::HIDDEN_POWER },
		{ "Hidden Power Electric", Moves::HIDDEN_POWER },
		{ "Hidden Power Fighting", Moves::HIDDEN_POWER },
		{ "Hidden Power Fire", Moves::HIDDEN_POWER },
		{ "Hidden Power Flying", Moves::HIDDEN_POWER },
		{ "Hidden Power Ghost", Moves::HIDDEN_POWER },
		{ "Hidden Power Grass", Moves::HIDDEN_POWER },
		{ "Hidden Power Ground", Moves::HIDDEN_POWER },
		{ "Hidden Power Ice", Moves::HIDDEN_POWER },
		{ "Hidden Power Poison", Moves::HIDDEN_POWER },
		{ "Hidden Power Psychic", Moves::HIDDEN_POWER },
		{ "Hidden Power Rock", Moves::HIDDEN_POWER },
		{ "Hidden Power Steel", Moves::HIDDEN_POWER },
		{ "Hidden Power Water", Moves::HIDDEN_POWER },
		{ "Horn Attack", Moves::HORN_ATTACK },
		{ "Horn Drill", Moves::HORN_DRILL },
		{ "Howl", Moves::HOWL },
		{ "Hydro Cannon", Moves::HYDRO_CANNON },
		{ "Hydro Pump", Moves::HYDRO_PUMP },
		{ "Hyper Beam", Moves::HYPER_BEAM },
		{ "Hyper Fang", Moves::HYPER_FANG },
		{ "Hyper Voice", Moves::HYPER_VOICE },
		{ "Hypnosis", Moves::HYPNOSIS },
		{ "Ice Ball", Moves::ICE_BALL },
		{ "Ice Beam", Moves::ICE_BEAM },
		{ "Ice Fang", Moves::ICE_FANG },
		{ "Ice Punch", Moves::ICE_PUNCH },
		{ "Ice Shard", Moves::ICE_SHARD },
		{ "Icicle Spear", Moves::ICICLE_SPEAR },
		{ "Icy Wind", Moves::ICY_WIND },
		{ "Imprison", Moves::IMPRISON },
		{ "Ingrain", Moves::INGRAIN },
		{ "Iron Defense", Moves::IRON_DEFENSE },
		{ "Iron Head", Moves::IRON_HEAD },
		{ "Iron Tail", Moves::IRON_TAIL },
		{ "Judgment", Moves::JUDGMENT },
		{ "Jump Kick", Moves::JUMP_KICK },
		{ "Karate Chop", Moves::KARATE_CHOP },
		{ "Kinesis", Moves::KINESIS },
		{ "Knock Off", Moves::KNOCK_OFF },
		{ "Last Resort", Moves::LAST_RESORT },
		{ "Lava Plume", Moves::LAVA_PLUME },
		{ "Leaf Blade", Moves::LEAF_BLADE },
		{ "Leaf Storm", Moves::LEAF_STORM },
		{ "Leech Life", Moves::LEECH_LIFE },
		{ "Leech Seed", Moves::LEECH_SEED },
		{ "Leer", Moves::LEER },
		{ "Lick", Moves::LICK },
		{ "Light Screen", Moves::LIGHT_SCREEN },
		{ "Lock-On", Moves::LOCK_ON },
		{ "Lock-on", Moves::LOCK_ON },
		{ "Lovely Kiss", Moves::LOVELY_KISS },
		{ "Low Kick", Moves::LOW_KICK },
		{ "Lucky Chant", Moves::LUCKY_CHANT },
		{ "Lunar Dance", Moves::LUNAR_DANCE },
		{ "Luster Purge", Moves::LUSTER_PURGE },
		{ "Mach Punch", Moves::MACH_PUNCH },
		{ "Magic Coat", Moves::MAGIC_COAT },
		{ "Magical Leaf", Moves::MAGICAL_LEAF },
		{ "Magma Storm", Moves::MAGMA_STORM },
		{ "Magnet Bomb", Moves::MAGNET_BOMB },
		{ "Magnet Rise", Moves::MAGNET_RISE },
		{ "Magnitude", Moves::MAGNITUDE },
		{ "Me First", Moves::ME_FIRST },
		{ "Mean Look", Moves::MEAN_LOOK },
		{ "Meditate", Moves::MEDITATE },
		{ "Mega Drain", Moves::MEGA_DRAIN },
		{ "Mega Kick", Moves::MEGA_KICK },
		{ "Mega Punch", Moves::MEGA_PUNCH },
		{ "Megahorn", Moves::MEGAHORN },
		{ "Memento", Moves::MEMENTO },
		{ "Metal Burst", Moves::METAL_BURST },
		{ "Metal Claw", Moves::METAL_CLAW },
		{ "Metal Sound", Moves::METAL_SOUND },
		{ "Meteor Mash", Moves::METEOR_MASH },
		{ "Metronome", Moves::METRONOME },
		{ "Milk Drink", Moves::MILK_DRINK },
		{ "Mimic", Moves::MIMIC },
		{ "Mind Reader", Moves::MIND_READER },
		{ "Minimize", Moves::MINIMIZE },
		{ "Miracle Eye", Moves::MIRACLE_EYE },
		{ "Mirror Coat", Moves::MIRROR_COAT },
		{ "Mirror Move", Moves::MIRROR_MOVE },
		{ "Mirror Shot", Moves::MIRROR_SHOT },
		{ "Mist", Moves::MIST },
		{ "Mist Ball", Moves::MIST_BALL },
		{ "Moonlight", Moves::MOONLIGHT },
		{ "Morning Sun", Moves::MORNING_SUN },
		{ "Mud Bomb", Moves::MUD_BOMB },
		{ "Mud Shot", Moves::MUD_SHOT },
		{ "Mud Sport", Moves::MUD_SPORT },
		{ "Mud-Slap", Moves::MUD_SLAP },
		{ "Mud-slap", Moves::MUD_SLAP },
		{ "Muddy Water", Moves::MUDDY_WATER },
		{ "Nasty Plot", Moves::NASTY_PLOT },
		{ "Natural Gift", Moves::NATURAL_GIFT },
		{ "Nature Power", Moves::NATURE_POWER },
		{ "Needle Arm", Moves::NEEDLE_ARM },
		{ "Night Shade", Moves::NIGHT_SHADE },
		{ "Night Slash", Moves::NIGHT_SLASH },
		{ "Nightmare", Moves::NIGHTMARE },
		{ "Octazooka", Moves::OCTAZOOKA },
		{ "Odor Sleuth", Moves::ODOR_SLEUTH },
		{ "Ominous Wind", Moves::OMINOUS_WIND },
		{ "Outrage", Moves::OUTRAGE },
		{ "Overheat", Moves::OVERHEAT },
		{ "Pain Split", Moves::PAIN_SPLIT },
		{ "Pay Day", Moves::PAY_DAY },
		{ "Payback", Moves::PAYBACK },
		{ "Peck", Moves::PECK },
		{ "Perish Song", Moves::PERISH_SONG },
		{ "Petal Dance", Moves::PETAL_DANCE },
		{ "Pin Missile", Moves::PIN_MISSILE },
		{ "Pluck", Moves::PLUCK },
		{ "Poison Fang", Moves::POISON_FANG },
		{ "Poison Gas", Moves::POISON_GAS },
		{ "Poison Jab", Moves::POISON_JAB },
		{ "Poison Sting", Moves::POISON_STING },
		{ "Poison Tail", Moves::POISON_TAIL },
		{ "PoisonPowder", Moves::POISONPOWDER },
		{ "Poisonpowder", Moves::POISONPOWDER },
		{ "Pound", Moves::POUND },
		{ "Powder Snow", Moves::POWDER_SNOW },
		{ "Power Gem", Moves::POWER_GEM },
		{ "Power Swap", Moves::POWER_SWAP },
		{ "Power Trick", Moves::POWER_TRICK },
		{ "Power Whip", Moves::POWER_WHIP },
		{ "Present", Moves::PRESENT },
		{ "Protect", Moves::PROTECT },
		{ "Psybeam", Moves::PSYBEAM },
		{ "Psych Up", Moves::PSYCH_UP },
		{ "Psychic", Moves::PSYCHIC },
		{ "Psycho Boost", Moves::PSYCHO_BOOST },
		{ "Psycho Cut", Moves::PSYCHO_CUT },
		{ "Psycho Shift", Moves::PSYCHO_SHIFT },
		{ "Psywave", Moves::PSYWAVE },
		{ "Punishment", Moves::PUNISHMENT },
		{ "Pursuit", Moves::PURSUIT },
		{ "Quick Attack", Moves::QUICK_ATTACK },
		{ "Rage", Moves::RAGE },
		{ "Rain Dance", Moves::RAIN_DANCE },
		{ "Rapid Spin", Moves::RAPID_SPIN },
		{ "Razor Leaf", Moves::RAZOR_LEAF },
		{ "Razor Wind", Moves::RAZOR_WIND },
		{ "Recover", Moves::RECOVER },
		{ "Recycle", Moves::RECYCLE },
		{ "Reflect", Moves::REFLECT },
		{ "Refresh", Moves::REFRESH },
		{ "Rest", Moves::REST },
		{ "Return", Moves::RETURN },
		{ "Revenge", Moves::REVENGE },
		{ "Reversal", Moves::REVERSAL },
		{ "Roar", Moves::ROAR },
		{ "Roar Of Time", Moves::ROAR_OF_TIME },
		{ "Rock Blast", Moves::ROCK_BLAST },
		{ "Rock Climb", Moves::ROCK_CLIMB },
		{ "Rock Polish", Moves::ROCK_POLISH },
		{ "Rock Slide", Moves::ROCK_SLIDE },
		{ "Rock Smash", Moves::ROCK_SMASH },
		{ "Rock Throw", Moves::ROCK_THROW },
		{ "Rock Tomb", Moves::ROCK_TOMB },
		{ "Rock Wrecker", Moves::ROCK_WRECKER },
		{ "Role Play", Moves::ROLE_PLAY },
		{ "Rolling Kick", Moves::ROLLING_KICK },
		{ "Rollout", Moves::ROLLOUT },
		{ "Roost", Moves::ROOST },
		{ "Sacred Fire", Moves::SACRED_FIRE },
		{ "Safeguard", Moves::SAFEGUARD },
		{ "Sand Tomb", Moves::SAND_TOMB },
		{ "Sand-Attack", Moves::SAND_ATTACK },
		{ "Sand-attack", Moves::SAND_ATTACK },
		{ "Sandstorm", Moves::SANDSTORM },
		{ "Scary Face", Moves::SCARY_FACE },
		{ "Scratch", Moves::SCRATCH },
		{ "Screech", Moves::SCREECH },
		{ "Secret Power", Moves::SECRET_POWER },
		{ "Seed Bomb", Moves::SEED_BOMB },
		{ "Seed Flare", Moves::SEED_FLARE },
		{ "Seismic Toss", Moves::SEISMIC_TOSS },
		{ "Selfdestruct", Moves::SELFDESTRUCT },
		{ "Shadow Ball", Moves::SHADOW_BALL },
		{ "Shadow Claw", Moves::SHADOW_CLAW },
		{ "Shadow Force", Moves::SHADOW_FORCE },
		{ "Shadow Punch", Moves::SHADOW_PUNCH },
		{ "Shadow Sneak", Moves::SHADOW_SNEAK },
		{ "Sharpen", Moves::SHARPEN },
		{ "Sheer Cold", Moves::SHEER_COLD },
		{ "Shock Wave", Moves::SHOCK_WAVE },
		{ "Signal Beam", Moves::SIGNAL_BEAM },
		{ "Silver Wind", Moves::SILVER_WIND },
		{ "Sing", Moves::SING },
		{ "Sketch", Moves::SKETCH },
		{ "Skill Swap", Moves::SKILL_SWAP },
		{ "Skull Bash", Moves::SKULL_BASH },
		{ "Sky Attack", Moves::SKY_ATTACK },
		{ "Sky Uppercut", Moves::SKY_UPPERCUT },
		{ "Slack Off", Moves::SLACK_OFF },
		{ "Slam", Moves::SLAM },
		{ "Slash", Moves::SLASH },
		{ "Sleep Powder", Moves::SLEEP_POWDER },
		{ "Sleep Talk", Moves::SLEEP_TALK },
		{ "Sludge", Moves::SLUDGE },
		{ "Sludge Bomb", Moves::SLUDGE_BOMB },
		{ "SmellingSalt", Moves::SMELLINGSALT },
		{ "Smellingsalt", Moves::SMELLINGSALT },
		{ "Smog", Moves::SMOG },
		{ "SmokeScreen", Moves::SMOKESCREEN },
		{ "Smokescreen", Moves::SMOKESCREEN },
		{ "Snatch", Moves::SNATCH },
		{ "Snore", Moves::SNORE },
		{ "Softboiled", Moves::SOFTBOILED },
		{ "SolarBeam", Moves::SOLARBEAM },
		{ "Solarbeam", Moves::SOLARBEAM },
		{ "SonicBoom", Moves::SONICBOOM },
		{ "Sonicboom", Moves::SONICBOOM },
		{ "Spacial Rend", Moves::SPACIAL_REND },
		{ "Spark", Moves::SPARK },
		{ "Spider Web", Moves::SPIDER_WEB },
		{ "Spike Cannon", Moves::SPIKE_CANNON },
		{ "Spikes", Moves::SPIKES },
		{ "Spit Up", Moves::SPIT_UP },
		{ "Spite", Moves::SPITE },
		{ "Splash", Moves::SPLASH },
		{ "Spore", Moves::SPORE },
		{ "Stealth Rock", Moves::STEALTH_ROCK },
		{ "Steel Wing", Moves::STEEL_WING },
		{ "Stockpile", Moves::STOCKPILE },
		{ "Stomp", Moves::STOMP },
		{ "Stone Edge", Moves::STONE_EDGE },
		{ "Strength", Moves::STRENGTH },
		{ "String Shot", Moves::STRING_SHOT },
		{ "Struggle", Moves::STRUGGLE },
		{ "Stun Spore", Moves::STUN_SPORE },
		{ "Submission", Moves::SUBMISSION },
		{ "Substitute", Moves::SUBSTITUTE },
		{ "Sucker Punch", Moves::SUCKER_PUNCH },
		{ "Sunny Day", Moves::SUNNY_DAY },
		{ "Super Fang", Moves::SUPER_FANG },
		{ "Superpower", Moves::SUPERPOWER },
		{ "Supersonic", Moves::SUPERSONIC },
		{ "Surf", Moves::SURF },
		{ "Swagger", Moves::SWAGGER },
		{ "Swallow", Moves::SWALLOW },
		{ "Sweet Kiss", Moves::SWEET_KISS },
		{ "Sweet Scent", Moves::SWEET_SCENT },
		{ "Swift", Moves::SWIFT },
		{ "Switch0", Moves::SWITCH0 },
		{ "Switch1", Moves::SWITCH1 },
		{ "Switch2", Moves::SWITCH2 },
		{ "Switch3", Moves::SWITCH3 },
		{ "Switch4", Moves::SWITCH4 },
		{ "Switch5", Moves::SWITCH5 },
		{ "Switcheroo", Moves::SWITCHEROO },
		{ "Swords Dance", Moves::SWORDS_DANCE },
		{ "Synthesis", Moves::SYNTHESIS },
		{ "Tackle", Moves::TACKLE },
		{ "Tail Glow", Moves::TAIL_GLOW },
		{ "Tail Whip", Moves::TAIL_WHIP },
		{ "Tailwind", Moves::TAILWIND },
		{ "Take Down", Moves::TAKE_DOWN },
		{ "Taunt", Moves::TAUNT },
		{ "Teeter Dance", Moves::TEETER_DANCE },
		{ "Teleport", Moves::TELEPORT },
		{ "Thief", Moves::THIEF },
		{ "Thrash", Moves::THRASH },
		{ "Thunder", Moves::THUNDER },
		{ "Thunder Fang", Moves::THUNDER_FANG },
		{ "Thunder Wave", Moves::THUNDER_WAVE },
		{ "Thunderbolt", Moves::THUNDERBOLT },
		{ "ThunderPunch", Moves::THUNDERPUNCH },
		{ "Thunderpunch", Moves::THUNDERPUNCH },
		{ "ThunderShock", Moves::THUNDERSHOCK },
		{ "Thundershock", Moves::THUNDERSHOCK },
		{ "Tickle", Moves::TICKLE },
		{ "Torment", Moves::TORMENT },
		{ "Toxic", Moves::TOXIC },
		{ "Toxic Spikes", Moves::TOXIC_SPIKES },
		{ "Transform", Moves::TRANSFORM },
		{ "Tri Attack", Moves::TRI_ATTACK },
		{ "Trick", Moves::TRICK },
		{ "Trick Room", Moves::TRICK_ROOM },
		{ "Triple Kick", Moves::TRIPLE_KICK },
		{ "Trump Card", Moves::TRUMP_CARD },
		{ "Twineedle", Moves::TWINEEDLE },
		{ "Twister", Moves::TWISTER },
		{ "U-turn", Moves::U_TURN },
		{ "Uproar", Moves::UPROAR },
		{ "Vacuum Wave", Moves::VACUUM_WAVE },
		{ "ViceGrip", Moves::VICEGRIP },
		{ "Vicegrip", Moves::VICEGRIP },
		{ "Vine Whip", Moves::VINE_WHIP },
		{ "Vital Throw", Moves::VITAL_THROW },
		{ "Volt Tackle", Moves::VOLT_TACKLE },
		{ "Wake-Up Slap", Moves::WAKE_UP_SLAP },
		{ "Wake-up Slap", Moves::WAKE_UP_SLAP },
		{ "Water Gun", Moves::WATER_GUN },
		{ "Water Pulse", Moves::WATER_PULSE },
		{ "Water Sport", Moves::WATER_SPORT },
		{ "Water Spout", Moves::WATER_SPOUT },
		{ "Waterfall", Moves::WATERFALL },
		{ "Weather Ball", Moves::WEATHER_BALL },
		{ "Whirlpool", Moves::WHIRLPOOL },
		{ "Whirlwind", Moves::WHIRLWIND },
		{ "Will-O-Wisp", Moves::WILL_O_WISP },
		{ "Will-o-Wisp", Moves::WILL_O_WISP },
		{ "Will-o-wisp", Moves::WILL_O_WISP },
		{ "Wing Attack", Moves::WING_ATTACK },
		{ "Wish", Moves::WISH },
		{ "Withdraw", Moves::WITHDRAW },
		{ "Wood Hammer", Moves::WOOD_HAMMER },
		{ "Worry Seed", Moves::WORRY_SEED },
		{ "Wrap", Moves::WRAP },
		{ "Wring Out", Moves::WRING_OUT },
		{ "X-Scissor", Moves::X_SCISSOR },
		{ "X-scissor", Moves::X_SCISSOR },
		{ "Yawn", Moves::YAWN },
		{ "Zap Cannon", Moves::ZAP_CANNON },
		{ "Zen Headbutt", Moves::ZEN_HEADBUTT },
		{ "END_MOVE", Moves::END }
	};
	auto const it = converter.find (str);
	if (it != converter.end ())
		return it->second;
	else
		throw InvalidFromStringConversion ("Move", str);
}

}	// namespace technicalmachine
