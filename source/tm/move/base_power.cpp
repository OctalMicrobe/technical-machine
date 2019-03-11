// Copyright (C) 2016 David Stone
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

#include <tm/move/base_power.hpp>

#include <tm/move/moves.hpp>

#include <cassert>

namespace technicalmachine {
using namespace bounded::literal;

auto base_power(Moves const move) -> bounded::optional<bounded::integer<0, 250>> {
	// It doesn't matter if variable_power happens to have the same value as
	// anything else, as long as it is not 0.
	static constexpr auto variable_power = 1_bi;
	switch (move) {
		case Moves::Pass: return 0_bi;
		case Moves::Switch0: return 0_bi;
		case Moves::Switch1: return 0_bi;
		case Moves::Switch2: return 0_bi;
		case Moves::Switch3: return 0_bi;
		case Moves::Switch4: return 0_bi;
		case Moves::Switch5: return 0_bi;
		case Moves::Hit_Self: return 40_bi;
		case Moves::Flash_Fire: return 0_bi;
		case Moves::Pound: return 40_bi;
		case Moves::Karate_Chop: return 50_bi;
		case Moves::DoubleSlap: return 15_bi;
		case Moves::Comet_Punch: return 18_bi;
		case Moves::Mega_Punch: return 80_bi;
		case Moves::Pay_Day: return 40_bi;
		case Moves::Fire_Punch: return 75_bi;
		case Moves::Ice_Punch: return 75_bi;
		case Moves::ThunderPunch: return 75_bi;
		case Moves::Scratch: return 40_bi;
		case Moves::ViceGrip: return 55_bi;
		case Moves::Guillotine: return bounded::none;
		case Moves::Razor_Wind: return 80_bi;
		case Moves::Swords_Dance: return 0_bi;
		case Moves::Cut: return 50_bi;
		case Moves::Gust: return 40_bi;
		case Moves::Wing_Attack: return 60_bi;
		case Moves::Whirlwind: return 0_bi;
		case Moves::Fly: return 90_bi;
		case Moves::Bind: return 15_bi;
		case Moves::Slam: return 80_bi;
		case Moves::Vine_Whip: return 35_bi;
		case Moves::Stomp: return 65_bi;
		case Moves::Double_Kick: return 30_bi;
		case Moves::Mega_Kick: return 120_bi;
		case Moves::Jump_Kick: return 100_bi;
		case Moves::Rolling_Kick: return 60_bi;
		case Moves::Sand_Attack: return 0_bi;
		case Moves::Headbutt: return 70_bi;
		case Moves::Horn_Attack: return 65_bi;
		case Moves::Fury_Attack: return 15_bi;
		case Moves::Horn_Drill: return bounded::none;
		case Moves::Tackle: return 50_bi;
		case Moves::Body_Slam: return 85_bi;
		case Moves::Wrap: return 15_bi;
		case Moves::Take_Down: return 90_bi;
		case Moves::Thrash: return 120_bi;
		case Moves::Double_Edge: return 120_bi;
		case Moves::Tail_Whip: return 0_bi;
		case Moves::Poison_Sting: return 15_bi;
		case Moves::Twineedle: return 25_bi;
		case Moves::Pin_Missile: return 14_bi;
		case Moves::Leer: return 0_bi;
		case Moves::Bite: return 60_bi;
		case Moves::Growl: return 0_bi;
		case Moves::Roar: return 0_bi;
		case Moves::Sing: return 0_bi;
		case Moves::Supersonic: return 0_bi;
		case Moves::SonicBoom: return bounded::none;
		case Moves::Disable: return 0_bi;
		case Moves::Acid: return 40_bi;
		case Moves::Ember: return 40_bi;
		case Moves::Flamethrower: return 95_bi;
		case Moves::Mist: return 0_bi;
		case Moves::Water_Gun: return 40_bi;
		case Moves::Hydro_Pump: return 120_bi;
		case Moves::Surf: return 95_bi;
		case Moves::Ice_Beam: return 95_bi;
		case Moves::Blizzard: return 120_bi;
		case Moves::Psybeam: return 65_bi;
		case Moves::BubbleBeam: return 65_bi;
		case Moves::Aurora_Beam: return 65_bi;
		case Moves::Hyper_Beam: return 150_bi;
		case Moves::Peck: return 35_bi;
		case Moves::Drill_Peck: return 80_bi;
		case Moves::Submission: return 80_bi;
		case Moves::Low_Kick: return variable_power;
		case Moves::Counter: return bounded::none;
		case Moves::Seismic_Toss: return bounded::none;
		case Moves::Strength: return 80_bi;
		case Moves::Absorb: return 20_bi;
		case Moves::Mega_Drain: return 40_bi;
		case Moves::Leech_Seed: return 0_bi;
		case Moves::Growth: return 0_bi;
		case Moves::Razor_Leaf: return 55_bi;
		case Moves::SolarBeam: return 120_bi;
		case Moves::PoisonPowder: return 0_bi;
		case Moves::Stun_Spore: return 0_bi;
		case Moves::Sleep_Powder: return 0_bi;
		case Moves::Petal_Dance: return 120_bi;
		case Moves::String_Shot: return 0_bi;
		case Moves::Dragon_Rage: return bounded::none;
		case Moves::Fire_Spin: return 35_bi;
		case Moves::ThunderShock: return 40_bi;
		case Moves::Thunderbolt: return 95_bi;
		case Moves::Thunder_Wave: return 0_bi;
		case Moves::Thunder: return 120_bi;
		case Moves::Rock_Throw: return 50_bi;
		case Moves::Earthquake: return 100_bi;
		case Moves::Fissure: return bounded::none;
		case Moves::Dig: return 80_bi;
		case Moves::Toxic: return 0_bi;
		case Moves::Confusion: return 50_bi;
		case Moves::Psychic: return 90_bi;
		case Moves::Hypnosis: return 0_bi;
		case Moves::Meditate: return 0_bi;
		case Moves::Agility: return 0_bi;
		case Moves::Quick_Attack: return 40_bi;
		case Moves::Rage: return 20_bi;
		case Moves::Teleport: return 0_bi;
		case Moves::Night_Shade: return bounded::none;
		case Moves::Mimic: return 0_bi;
		case Moves::Screech: return 0_bi;
		case Moves::Double_Team: return 0_bi;
		case Moves::Recover: return 0_bi;
		case Moves::Harden: return 0_bi;
		case Moves::Minimize: return 0_bi;
		case Moves::SmokeScreen: return 0_bi;
		case Moves::Confuse_Ray: return 0_bi;
		case Moves::Withdraw: return 0_bi;
		case Moves::Defense_Curl: return 0_bi;
		case Moves::Barrier: return 0_bi;
		case Moves::Light_Screen: return 0_bi;
		case Moves::Haze: return 0_bi;
		case Moves::Reflect: return 0_bi;
		case Moves::Focus_Energy: return 0_bi;
		case Moves::Bide: return variable_power;
		case Moves::Metronome: return 0_bi;
		case Moves::Mirror_Move: return 0_bi;
		case Moves::Selfdestruct: return 200_bi;
		case Moves::Egg_Bomb: return 100_bi;
		case Moves::Lick: return 20_bi;
		case Moves::Smog: return 20_bi;
		case Moves::Sludge: return 65_bi;
		case Moves::Bone_Club: return 65_bi;
		case Moves::Fire_Blast: return 120_bi;
		case Moves::Waterfall: return 80_bi;
		case Moves::Clamp: return 35_bi;
		case Moves::Swift: return 60_bi;
		case Moves::Skull_Bash: return 100_bi;
		case Moves::Spike_Cannon: return 20_bi;
		case Moves::Constrict: return 10_bi;
		case Moves::Amnesia: return 0_bi;
		case Moves::Kinesis: return 0_bi;
		case Moves::Softboiled: return 0_bi;
		case Moves::Hi_Jump_Kick: return 130_bi;
		case Moves::Glare: return 0_bi;
		case Moves::Dream_Eater: return 100_bi;
		case Moves::Poison_Gas: return 0_bi;
		case Moves::Barrage: return 15_bi;
		case Moves::Leech_Life: return 20_bi;
		case Moves::Lovely_Kiss: return 0_bi;
		case Moves::Sky_Attack: return 140_bi;
		case Moves::Transform: return 0_bi;
		case Moves::Bubble: return 20_bi;
		case Moves::Dizzy_Punch: return 70_bi;
		case Moves::Spore: return 0_bi;
		case Moves::Flash: return 0_bi;
		case Moves::Psywave: return bounded::none;
		case Moves::Splash: return 0_bi;
		case Moves::Acid_Armor: return 0_bi;
		case Moves::Crabhammer: return 90_bi;
		case Moves::Explosion: return 250_bi;
		case Moves::Fury_Swipes: return 18_bi;
		case Moves::Bonemerang: return 50_bi;
		case Moves::Rest: return 0_bi;
		case Moves::Rock_Slide: return 75_bi;
		case Moves::Hyper_Fang: return 80_bi;
		case Moves::Sharpen: return 0_bi;
		case Moves::Conversion: return 0_bi;
		case Moves::Tri_Attack: return 80_bi;
		case Moves::Super_Fang: return bounded::none;
		case Moves::Slash: return 70_bi;
		case Moves::Substitute: return 0_bi;
		case Moves::Struggle: return 50_bi;
		case Moves::Sketch: return 0_bi;
		case Moves::Triple_Kick: return 10_bi;
		case Moves::Thief: return 40_bi;
		case Moves::Spider_Web: return 0_bi;
		case Moves::Mind_Reader: return 0_bi;
		case Moves::Nightmare: return 0_bi;
		case Moves::Flame_Wheel: return 60_bi;
		case Moves::Snore: return 40_bi;
		case Moves::Curse: return 0_bi;
		case Moves::Flail: return variable_power;
		case Moves::Conversion_2: return 0_bi;
		case Moves::Aeroblast: return 100_bi;
		case Moves::Cotton_Spore: return 0_bi;
		case Moves::Reversal: return variable_power;
		case Moves::Spite: return 0_bi;
		case Moves::Powder_Snow: return 40_bi;
		case Moves::Protect: return 0_bi;
		case Moves::Mach_Punch: return 40_bi;
		case Moves::Scary_Face: return 0_bi;
		case Moves::Faint_Attack: return 60_bi;
		case Moves::Sweet_Kiss: return 0_bi;
		case Moves::Belly_Drum: return 0_bi;
		case Moves::Sludge_Bomb: return 90_bi;
		case Moves::Mud_Slap: return 20_bi;
		case Moves::Octazooka: return 65_bi;
		case Moves::Spikes: return 0_bi;
		case Moves::Zap_Cannon: return 120_bi;
		case Moves::Foresight: return 0_bi;
		case Moves::Destiny_Bond: return 0_bi;
		case Moves::Perish_Song: return 0_bi;
		case Moves::Icy_Wind: return 55_bi;
		case Moves::Detect: return 0_bi;
		case Moves::Bone_Rush: return 25_bi;
		case Moves::Lock_On: return 0_bi;
		case Moves::Outrage: return 120_bi;
		case Moves::Sandstorm: return 0_bi;
		case Moves::Giga_Drain: return 75_bi;
		case Moves::Endure: return 0_bi;
		case Moves::Charm: return 0_bi;
		case Moves::Rollout: return 30_bi;
		case Moves::False_Swipe: return 40_bi;
		case Moves::Swagger: return 0_bi;
		case Moves::Milk_Drink: return 0_bi;
		case Moves::Spark: return 65_bi;
		case Moves::Fury_Cutter: return 20_bi;
		case Moves::Steel_Wing: return 70_bi;
		case Moves::Mean_Look: return 0_bi;
		case Moves::Attract: return 0_bi;
		case Moves::Sleep_Talk: return 0_bi;
		case Moves::Heal_Bell: return 0_bi;
		case Moves::Return: return variable_power;
		case Moves::Present: return variable_power;
		case Moves::Frustration: return variable_power;
		case Moves::Safeguard: return 0_bi;
		case Moves::Pain_Split: return 0_bi;
		case Moves::Sacred_Fire: return 100_bi;
		case Moves::Magnitude: return variable_power;
		case Moves::DynamicPunch: return 100_bi;
		case Moves::Megahorn: return 120_bi;
		case Moves::DragonBreath: return 60_bi;
		case Moves::Baton_Pass: return 0_bi;
		case Moves::Encore: return 0_bi;
		case Moves::Pursuit: return 40_bi;
		case Moves::Rapid_Spin: return 20_bi;
		case Moves::Sweet_Scent: return 0_bi;
		case Moves::Iron_Tail: return 100_bi;
		case Moves::Metal_Claw: return 50_bi;
		case Moves::Vital_Throw: return 70_bi;
		case Moves::Morning_Sun: return 0_bi;
		case Moves::Synthesis: return 0_bi;
		case Moves::Moonlight: return 0_bi;
		case Moves::Hidden_Power: return variable_power;
		case Moves::Cross_Chop: return 100_bi;
		case Moves::Twister: return 40_bi;
		case Moves::Rain_Dance: return 0_bi;
		case Moves::Sunny_Day: return 0_bi;
		case Moves::Crunch: return 80_bi;
		case Moves::Mirror_Coat: return bounded::none;
		case Moves::Psych_Up: return 0_bi;
		case Moves::ExtremeSpeed: return 80_bi;
		case Moves::AncientPower: return 60_bi;
		case Moves::Shadow_Ball: return 80_bi;
		case Moves::Future_Sight: return 100_bi;
		case Moves::Rock_Smash: return 40_bi;
		case Moves::Whirlpool: return 35_bi;
		case Moves::Beat_Up: return variable_power;
		case Moves::Fake_Out: return 40_bi;
		case Moves::Uproar: return 90_bi;
		case Moves::Stockpile: return 0_bi;
		case Moves::Spit_Up: return variable_power;
		case Moves::Swallow: return 0_bi;
		case Moves::Heat_Wave: return 100_bi;
		case Moves::Hail: return 0_bi;
		case Moves::Torment: return 0_bi;
		case Moves::Flatter: return 0_bi;
		case Moves::Will_O_Wisp: return 0_bi;
		case Moves::Memento: return 0_bi;
		case Moves::Facade: return 70_bi;
		case Moves::Focus_Punch: return 150_bi;
		case Moves::SmellingSalt: return 60_bi;
		case Moves::Follow_Me: return 0_bi;
		case Moves::Nature_Power: return 0_bi;
		case Moves::Charge: return 0_bi;
		case Moves::Taunt: return 0_bi;
		case Moves::Helping_Hand: return 0_bi;
		case Moves::Trick: return 0_bi;
		case Moves::Role_Play: return 0_bi;
		case Moves::Wish: return 0_bi;
		case Moves::Assist: return 0_bi;
		case Moves::Ingrain: return 0_bi;
		case Moves::Superpower: return 120_bi;
		case Moves::Magic_Coat: return 0_bi;
		case Moves::Recycle: return 0_bi;
		case Moves::Revenge: return 60_bi;
		case Moves::Brick_Break: return 75_bi;
		case Moves::Yawn: return 0_bi;
		case Moves::Knock_Off: return 20_bi;
		case Moves::Endeavor: return bounded::none;
		case Moves::Eruption: return 150_bi;
		case Moves::Skill_Swap: return 0_bi;
		case Moves::Imprison: return 0_bi;
		case Moves::Refresh: return 0_bi;
		case Moves::Grudge: return 0_bi;
		case Moves::Snatch: return 0_bi;
		case Moves::Secret_Power: return 70_bi;
		case Moves::Dive: return 80_bi;
		case Moves::Arm_Thrust: return 15_bi;
		case Moves::Camouflage: return 0_bi;
		case Moves::Tail_Glow: return 0_bi;
		case Moves::Luster_Purge: return 70_bi;
		case Moves::Mist_Ball: return 70_bi;
		case Moves::FeatherDance: return 0_bi;
		case Moves::Teeter_Dance: return 0_bi;
		case Moves::Blaze_Kick: return 85_bi;
		case Moves::Mud_Sport: return 0_bi;
		case Moves::Ice_Ball: return 30_bi;
		case Moves::Needle_Arm: return 60_bi;
		case Moves::Slack_Off: return 0_bi;
		case Moves::Hyper_Voice: return 90_bi;
		case Moves::Poison_Fang: return 50_bi;
		case Moves::Crush_Claw: return 75_bi;
		case Moves::Blast_Burn: return 150_bi;
		case Moves::Hydro_Cannon: return 150_bi;
		case Moves::Meteor_Mash: return 100_bi;
		case Moves::Astonish: return 30_bi;
		case Moves::Weather_Ball: return 50_bi;
		case Moves::Aromatherapy: return 0_bi;
		case Moves::Fake_Tears: return 0_bi;
		case Moves::Air_Cutter: return 55_bi;
		case Moves::Overheat: return 140_bi;
		case Moves::Odor_Sleuth: return 0_bi;
		case Moves::Rock_Tomb: return 50_bi;
		case Moves::Silver_Wind: return 60_bi;
		case Moves::Metal_Sound: return 0_bi;
		case Moves::GrassWhistle: return 0_bi;
		case Moves::Tickle: return 0_bi;
		case Moves::Cosmic_Power: return 0_bi;
		case Moves::Water_Spout: return 150_bi;
		case Moves::Signal_Beam: return 75_bi;
		case Moves::Shadow_Punch: return 60_bi;
		case Moves::Extrasensory: return 80_bi;
		case Moves::Sky_Uppercut: return 85_bi;
		case Moves::Sand_Tomb: return 35_bi;
		case Moves::Sheer_Cold: return bounded::none;
		case Moves::Muddy_Water: return 95_bi;
		case Moves::Bullet_Seed: return 25_bi;
		case Moves::Aerial_Ace: return 60_bi;
		case Moves::Icicle_Spear: return 25_bi;
		case Moves::Iron_Defense: return 0_bi;
		case Moves::Block: return 0_bi;
		case Moves::Howl: return 0_bi;
		case Moves::Dragon_Claw: return 80_bi;
		case Moves::Frenzy_Plant: return 150_bi;
		case Moves::Bulk_Up: return 0_bi;
		case Moves::Bounce: return 85_bi;
		case Moves::Mud_Shot: return 55_bi;
		case Moves::Poison_Tail: return 50_bi;
		case Moves::Covet: return 60_bi;
		case Moves::Volt_Tackle: return 120_bi;
		case Moves::Magical_Leaf: return 60_bi;
		case Moves::Water_Sport: return 0_bi;
		case Moves::Calm_Mind: return 0_bi;
		case Moves::Leaf_Blade: return 90_bi;
		case Moves::Dragon_Dance: return 0_bi;
		case Moves::Rock_Blast: return 25_bi;
		case Moves::Shock_Wave: return 60_bi;
		case Moves::Water_Pulse: return 60_bi;
		case Moves::Doom_Desire: return 140_bi;
		case Moves::Psycho_Boost: return 140_bi;
		case Moves::Roost: return 0_bi;
		case Moves::Gravity: return 0_bi;
		case Moves::Miracle_Eye: return 0_bi;
		case Moves::Wake_Up_Slap: return 60_bi;
		case Moves::Hammer_Arm: return 100_bi;
		case Moves::Gyro_Ball: return variable_power;
		case Moves::Healing_Wish: return 0_bi;
		case Moves::Brine: return 65_bi;
		case Moves::Natural_Gift: return variable_power;
		case Moves::Feint: return 30_bi;
		case Moves::Pluck: return 60_bi;
		case Moves::Tailwind: return 0_bi;
		case Moves::Acupressure: return 0_bi;
		case Moves::Metal_Burst: return bounded::none;
		case Moves::U_turn: return 70_bi;
		case Moves::Close_Combat: return 120_bi;
		case Moves::Payback: return 50_bi;
		case Moves::Assurance: return 50_bi;
		case Moves::Embargo: return 0_bi;
		case Moves::Fling: return variable_power;
		case Moves::Psycho_Shift: return 0_bi;
		case Moves::Trump_Card: return variable_power;
		case Moves::Heal_Block: return 0_bi;
		case Moves::Wring_Out: return variable_power;
		case Moves::Power_Trick: return 0_bi;
		case Moves::Gastro_Acid: return 0_bi;
		case Moves::Lucky_Chant: return 0_bi;
		case Moves::Me_First: return variable_power;
		case Moves::Copycat: return 0_bi;
		case Moves::Power_Swap: return 0_bi;
		case Moves::Guard_Swap: return 0_bi;
		case Moves::Punishment: return variable_power;
		case Moves::Last_Resort: return 140_bi;
		case Moves::Worry_Seed: return 0_bi;
		case Moves::Sucker_Punch: return 80_bi;
		case Moves::Toxic_Spikes: return 0_bi;
		case Moves::Heart_Swap: return 0_bi;
		case Moves::Aqua_Ring: return 0_bi;
		case Moves::Magnet_Rise: return 0_bi;
		case Moves::Flare_Blitz: return 120_bi;
		case Moves::Force_Palm: return 60_bi;
		case Moves::Aura_Sphere: return 90_bi;
		case Moves::Rock_Polish: return 0_bi;
		case Moves::Poison_Jab: return 80_bi;
		case Moves::Dark_Pulse: return 80_bi;
		case Moves::Night_Slash: return 70_bi;
		case Moves::Aqua_Tail: return 90_bi;
		case Moves::Seed_Bomb: return 80_bi;
		case Moves::Air_Slash: return 75_bi;
		case Moves::X_Scissor: return 80_bi;
		case Moves::Bug_Buzz: return 90_bi;
		case Moves::Dragon_Pulse: return 90_bi;
		case Moves::Dragon_Rush: return 100_bi;
		case Moves::Power_Gem: return 70_bi;
		case Moves::Drain_Punch: return 75_bi;
		case Moves::Vacuum_Wave: return 40_bi;
		case Moves::Focus_Blast: return 120_bi;
		case Moves::Energy_Ball: return 80_bi;
		case Moves::Brave_Bird: return 120_bi;
		case Moves::Earth_Power: return 90_bi;
		case Moves::Switcheroo: return 0_bi;
		case Moves::Giga_Impact: return 150_bi;
		case Moves::Nasty_Plot: return 0_bi;
		case Moves::Bullet_Punch: return 40_bi;
		case Moves::Avalanche: return 60_bi;
		case Moves::Ice_Shard: return 40_bi;
		case Moves::Shadow_Claw: return 70_bi;
		case Moves::Thunder_Fang: return 65_bi;
		case Moves::Ice_Fang: return 65_bi;
		case Moves::Fire_Fang: return 65_bi;
		case Moves::Shadow_Sneak: return 40_bi;
		case Moves::Mud_Bomb: return 65_bi;
		case Moves::Psycho_Cut: return 70_bi;
		case Moves::Zen_Headbutt: return 80_bi;
		case Moves::Mirror_Shot: return 65_bi;
		case Moves::Flash_Cannon: return 80_bi;
		case Moves::Rock_Climb: return 90_bi;
		case Moves::Defog: return 0_bi;
		case Moves::Trick_Room: return 0_bi;
		case Moves::Draco_Meteor: return 140_bi;
		case Moves::Discharge: return 80_bi;
		case Moves::Lava_Plume: return 80_bi;
		case Moves::Leaf_Storm: return 140_bi;
		case Moves::Power_Whip: return 120_bi;
		case Moves::Rock_Wrecker: return 150_bi;
		case Moves::Cross_Poison: return 70_bi;
		case Moves::Gunk_Shot: return 120_bi;
		case Moves::Iron_Head: return 80_bi;
		case Moves::Magnet_Bomb: return 60_bi;
		case Moves::Stone_Edge: return 100_bi;
		case Moves::Captivate: return 0_bi;
		case Moves::Stealth_Rock: return 0_bi;
		case Moves::Grass_Knot: return variable_power;
		case Moves::Chatter: return 60_bi;
		case Moves::Judgment: return 100_bi;
		case Moves::Bug_Bite: return 60_bi;
		case Moves::Charge_Beam: return 50_bi;
		case Moves::Wood_Hammer: return 120_bi;
		case Moves::Aqua_Jet: return 40_bi;
		case Moves::Attack_Order: return 90_bi;
		case Moves::Defend_Order: return 0_bi;
		case Moves::Heal_Order: return 0_bi;
		case Moves::Head_Smash: return 150_bi;
		case Moves::Double_Hit: return 35_bi;
		case Moves::Roar_of_Time: return 150_bi;
		case Moves::Spacial_Rend: return 100_bi;
		case Moves::Lunar_Dance: return 0_bi;
		case Moves::Crush_Grip: return variable_power;
		case Moves::Magma_Storm: return 120_bi;
		case Moves::Dark_Void: return 0_bi;
		case Moves::Seed_Flare: return 120_bi;
		case Moves::Ominous_Wind: return 60_bi;
		case Moves::Shadow_Force: return 120_bi;
		case Moves::Hone_Claws: return 0_bi;
		case Moves::Wide_Guard: return 0_bi;
		case Moves::Guard_Split: return 0_bi;
		case Moves::Power_Split: return 0_bi;
		case Moves::Wonder_Room: return 0_bi;
		case Moves::Psyshock: return 80_bi;
		case Moves::Venoshock: return 65_bi;
		case Moves::Autotomize: return 0_bi;
		case Moves::Rage_Powder: return 0_bi;
		case Moves::Telekinesis: return 0_bi;
		case Moves::Magic_Room: return 0_bi;
		case Moves::Smack_Down: return 50_bi;
		case Moves::Storm_Throw: return 40_bi;
		case Moves::Flame_Burst: return 70_bi;
		case Moves::Sludge_Wave: return 95_bi;
		case Moves::Quiver_Dance: return 0_bi;
		case Moves::Heavy_Slam: return variable_power;
		case Moves::Synchronoise: return 70_bi;
		case Moves::Electro_Ball: return variable_power;
		case Moves::Soak: return 0_bi;
		case Moves::Flame_Charge: return 50_bi;
		case Moves::Coil: return 0_bi;
		case Moves::Low_Sweep: return 60_bi;
		case Moves::Acid_Spray: return 40_bi;
		case Moves::Foul_Play: return 95_bi;
		case Moves::Simple_Beam: return 0_bi;
		case Moves::Entrainment: return 0_bi;
		case Moves::After_You: return 0_bi;
		case Moves::Round: return 60_bi;
		case Moves::Echoed_Voice: return 40_bi;
		case Moves::Chip_Away: return 70_bi;
		case Moves::Clear_Smog: return 50_bi;
		case Moves::Stored_Power: return 20_bi;
		case Moves::Quick_Guard: return 0_bi;
		case Moves::Ally_Switch: return 0_bi;
		case Moves::Scald: return 80_bi;
		case Moves::Shell_Smash: return 0_bi;
		case Moves::Heal_Pulse: return 0_bi;
		case Moves::Hex: return 50_bi;
		case Moves::Sky_Drop: return 60_bi;
		case Moves::Shift_Gear: return 0_bi;
		case Moves::Circle_Throw: return 60_bi;
		case Moves::Incinerate: return 30_bi;
		case Moves::Quash: return 0_bi;
		case Moves::Acrobatics: return 55_bi;
		case Moves::Reflect_Type: return 0_bi;
		case Moves::Retaliate: return 70_bi;
		case Moves::Final_Gambit: return bounded::none;
		case Moves::Bestow: return 0_bi;
		case Moves::Inferno: return 100_bi;
		case Moves::Water_Pledge: return 50_bi;
		case Moves::Fire_Pledge: return 50_bi;
		case Moves::Grass_Pledge: return 50_bi;
		case Moves::Volt_Switch: return 70_bi;
		case Moves::Struggle_Bug: return 30_bi;
		case Moves::Bulldoze: return 60_bi;
		case Moves::Frost_Breath: return 40_bi;
		case Moves::Dragon_Tail: return 60_bi;
		case Moves::Work_Up: return 0_bi;
		case Moves::Electroweb: return 55_bi;
		case Moves::Wild_Charge: return 90_bi;
		case Moves::Drill_Run: return 80_bi;
		case Moves::Dual_Chop: return 40_bi;
		case Moves::Heart_Stamp: return 60_bi;
		case Moves::Horn_Leech: return 75_bi;
		case Moves::Sacred_Sword: return 90_bi;
		case Moves::Razor_Shell: return 75_bi;
		case Moves::Heat_Crash: return variable_power;
		case Moves::Leaf_Tornado: return 65_bi;
		case Moves::Steamroller: return 65_bi;
		case Moves::Cotton_Guard: return 0_bi;
		case Moves::Night_Daze: return 85_bi;
		case Moves::Psystrike: return 100_bi;
		case Moves::Tail_Slap: return 25_bi;
		case Moves::Hurricane: return 120_bi;
		case Moves::Head_Charge: return 120_bi;
		case Moves::Gear_Grind: return 50_bi;
		case Moves::Searing_Shot: return 100_bi;
		case Moves::Techno_Blast: return 85_bi;
		case Moves::Relic_Song: return 75_bi;
		case Moves::Secret_Sword: return 85_bi;
		case Moves::Glaciate: return 65_bi;
		case Moves::Bolt_Strike: return 130_bi;
		case Moves::Blue_Flare: return 130_bi;
		case Moves::Fiery_Dance: return 80_bi;
		case Moves::Freeze_Shock: return 140_bi;
		case Moves::Ice_Burn: return 140_bi;
		case Moves::Snarl: return 55_bi;
		case Moves::Icicle_Crash: return 85_bi;
		case Moves::V_create: return 180_bi;
		case Moves::Fusion_Flare: return 100_bi;
		case Moves::Fusion_Bolt: return 100_bi;
	}
}

}	// namespace technicalmachine
