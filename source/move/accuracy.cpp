// Accuracy functions
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

#include "accuracy.hpp"

#include "moves.hpp"

#include <stdexcept>

namespace technicalmachine {
using namespace bounded::literal;
namespace {

struct InvalidMove : std::exception {};

}	// namespace

auto accuracy(Moves const move) -> BaseAccuracy {
	using bounded::none;
	switch (move) {
		case Moves::Switch0: return none;
		case Moves::Switch1: return none;
		case Moves::Switch2: return none;
		case Moves::Switch3: return none;
		case Moves::Switch4: return none;
		case Moves::Switch5: return none;
		case Moves::Hit_Self: return none;
		case Moves::Pound: return 100_bi;
		case Moves::Karate_Chop: return 100_bi;
		case Moves::DoubleSlap: return 85_bi;
		case Moves::Comet_Punch: return 85_bi;
		case Moves::Mega_Punch: return 85_bi;
		case Moves::Pay_Day: return 100_bi;
		case Moves::Fire_Punch: return 100_bi;
		case Moves::Ice_Punch: return 100_bi;
		case Moves::ThunderPunch: return 100_bi;
		case Moves::Scratch: return 100_bi;
		case Moves::ViceGrip: return 100_bi;
		case Moves::Guillotine: return 30_bi;
		case Moves::Razor_Wind: return 100_bi;
		case Moves::Swords_Dance: return none;
		case Moves::Cut: return 95_bi;
		case Moves::Gust: return 100_bi;
		case Moves::Wing_Attack: return 100_bi;
		case Moves::Whirlwind: return 100_bi;
		case Moves::Fly: return 95_bi;
		case Moves::Bind: return 85_bi;
		case Moves::Slam: return 75_bi;
		case Moves::Vine_Whip: return 100_bi;
		case Moves::Stomp: return 100_bi;
		case Moves::Double_Kick: return 100_bi;
		case Moves::Mega_Kick: return 75_bi;
		case Moves::Jump_Kick: return 95_bi;
		case Moves::Rolling_Kick: return 85_bi;
		case Moves::Sand_Attack: return 100_bi;
		case Moves::Headbutt: return 100_bi;
		case Moves::Horn_Attack: return 100_bi;
		case Moves::Fury_Attack: return 85_bi;
		case Moves::Horn_Drill: return 30_bi;
		case Moves::Tackle: return 100_bi;
		case Moves::Body_Slam: return 100_bi;
		case Moves::Wrap: return 90_bi;
		case Moves::Take_Down: return 85_bi;
		case Moves::Thrash: return 100_bi;
		case Moves::Double_Edge: return 100_bi;
		case Moves::Tail_Whip: return 100_bi;
		case Moves::Poison_Sting: return 100_bi;
		case Moves::Twineedle: return 100_bi;
		case Moves::Pin_Missile: return 85_bi;
		case Moves::Leer: return 100_bi;
		case Moves::Bite: return 100_bi;
		case Moves::Growl: return 100_bi;
		case Moves::Roar: return 100_bi;
		case Moves::Sing: return 55_bi;
		case Moves::Supersonic: return 55_bi;
		case Moves::SonicBoom: return 90_bi;
		case Moves::Disable: return 100_bi;
		case Moves::Acid: return 100_bi;
		case Moves::Ember: return 100_bi;
		case Moves::Flamethrower: return 100_bi;
		case Moves::Mist: return none;
		case Moves::Water_Gun: return 100_bi;
		case Moves::Hydro_Pump: return 80_bi;
		case Moves::Surf: return 100_bi;
		case Moves::Ice_Beam: return 100_bi;
		case Moves::Blizzard: return 70_bi;
		case Moves::Psybeam: return 100_bi;
		case Moves::BubbleBeam: return 100_bi;
		case Moves::Aurora_Beam: return 100_bi;
		case Moves::Hyper_Beam: return 90_bi;
		case Moves::Peck: return 100_bi;
		case Moves::Drill_Peck: return 100_bi;
		case Moves::Submission: return 80_bi;
		case Moves::Low_Kick: return 100_bi;
		case Moves::Counter: return 100_bi;
		case Moves::Seismic_Toss: return 100_bi;
		case Moves::Strength: return 100_bi;
		case Moves::Absorb: return 100_bi;
		case Moves::Mega_Drain: return 100_bi;
		case Moves::Leech_Seed: return 90_bi;
		case Moves::Growth: return none;
		case Moves::Razor_Leaf: return 95_bi;
		case Moves::SolarBeam: return 100_bi;
		case Moves::PoisonPowder: return 75_bi;
		case Moves::Stun_Spore: return 75_bi;
		case Moves::Sleep_Powder: return 75_bi;
		case Moves::Petal_Dance: return 100_bi;
		case Moves::String_Shot: return 95_bi;
		case Moves::Dragon_Rage: return 100_bi;
		case Moves::Fire_Spin: return 85_bi;
		case Moves::ThunderShock: return 100_bi;
		case Moves::Thunderbolt: return 100_bi;
		case Moves::Thunder_Wave: return 100_bi;
		case Moves::Thunder: return 70_bi;
		case Moves::Rock_Throw: return 90_bi;
		case Moves::Earthquake: return 100_bi;
		case Moves::Fissure: return 30_bi;
		case Moves::Dig: return 100_bi;
		case Moves::Toxic: return 90_bi;
		case Moves::Confusion: return 100_bi;
		case Moves::Psychic: return 100_bi;
		case Moves::Hypnosis: return 60_bi;
		case Moves::Meditate: return none;
		case Moves::Agility: return none;
		case Moves::Quick_Attack: return 100_bi;
		case Moves::Rage: return 100_bi;
		case Moves::Teleport: return none;
		case Moves::Night_Shade: return 100_bi;
		case Moves::Mimic: return none;
		case Moves::Screech: return 85_bi;
		case Moves::Double_Team: return none;
		case Moves::Recover: return none;
		case Moves::Harden: return none;
		case Moves::Minimize: return none;
		case Moves::SmokeScreen: return 100_bi;
		case Moves::Confuse_Ray: return 100_bi;
		case Moves::Withdraw: return none;
		case Moves::Defense_Curl: return none;
		case Moves::Barrier: return none;
		case Moves::Light_Screen: return none;
		case Moves::Haze: return none;
		case Moves::Reflect: return none;
		case Moves::Focus_Energy: return none;
		case Moves::Bide: return none;
		case Moves::Metronome: return none;
		case Moves::Mirror_Move: return none;
		case Moves::Selfdestruct: return 100_bi;
		case Moves::Egg_Bomb: return 75_bi;
		case Moves::Lick: return 100_bi;
		case Moves::Smog: return 70_bi;
		case Moves::Sludge: return 100_bi;
		case Moves::Bone_Club: return 85_bi;
		case Moves::Fire_Blast: return 85_bi;
		case Moves::Waterfall: return 100_bi;
		case Moves::Clamp: return 85_bi;
		case Moves::Swift: return none;
		case Moves::Skull_Bash: return 100_bi;
		case Moves::Spike_Cannon: return 100_bi;
		case Moves::Constrict: return 100_bi;
		case Moves::Amnesia: return none;
		case Moves::Kinesis: return 80_bi;
		case Moves::Softboiled: return none;
		case Moves::Hi_Jump_Kick: return 90_bi;
		case Moves::Glare: return 90_bi;
		case Moves::Dream_Eater: return 100_bi;
		case Moves::Poison_Gas: return 80_bi;
		case Moves::Barrage: return 85_bi;
		case Moves::Leech_Life: return 100_bi;
		case Moves::Lovely_Kiss: return 75_bi;
		case Moves::Sky_Attack: return 90_bi;
		case Moves::Transform: return none;
		case Moves::Bubble: return 100_bi;
		case Moves::Dizzy_Punch: return 100_bi;
		case Moves::Spore: return 100_bi;
		case Moves::Flash: return 100_bi;
		case Moves::Psywave: return 80_bi;
		case Moves::Splash: return none;
		case Moves::Acid_Armor: return none;
		case Moves::Crabhammer: return 90_bi;
		case Moves::Explosion: return 100_bi;
		case Moves::Fury_Swipes: return 80_bi;
		case Moves::Bonemerang: return 90_bi;
		case Moves::Rest: return none;
		case Moves::Rock_Slide: return 90_bi;
		case Moves::Hyper_Fang: return 90_bi;
		case Moves::Sharpen: return none;
		case Moves::Conversion: return none;
		case Moves::Tri_Attack: return 100_bi;
		case Moves::Super_Fang: return 90_bi;
		case Moves::Slash: return 100_bi;
		case Moves::Substitute: return none;
		case Moves::Struggle: return none;
		case Moves::Sketch: return none;
		case Moves::Triple_Kick: return 90_bi;
		case Moves::Thief: return 100_bi;
		case Moves::Spider_Web: return none;
		case Moves::Mind_Reader: return none;
		case Moves::Nightmare: return 100_bi;
		case Moves::Flame_Wheel: return 100_bi;
		case Moves::Snore: return 100_bi;
		case Moves::Curse: return none;
		case Moves::Flail: return 100_bi;
		case Moves::Conversion_2: return none;
		case Moves::Aeroblast: return 95_bi;
		case Moves::Cotton_Spore: return 100_bi;
		case Moves::Reversal: return 100_bi;
		case Moves::Spite: return 100_bi;
		case Moves::Powder_Snow: return 100_bi;
		case Moves::Protect: return none;
		case Moves::Mach_Punch: return 100_bi;
		case Moves::Scary_Face: return 100_bi;
		case Moves::Faint_Attack: return none;
		case Moves::Sweet_Kiss: return 75_bi;
		case Moves::Belly_Drum: return none;
		case Moves::Sludge_Bomb: return 100_bi;
		case Moves::Mud_Slap: return 100_bi;
		case Moves::Octazooka: return 85_bi;
		case Moves::Spikes: return none;
		case Moves::Zap_Cannon: return 50_bi;
		case Moves::Foresight: return none;
		case Moves::Destiny_Bond: return none;
		case Moves::Perish_Song: return none;
		case Moves::Icy_Wind: return 95_bi;
		case Moves::Detect: return none;
		case Moves::Bone_Rush: return 90_bi;
		case Moves::Lock_On: return none;
		case Moves::Outrage: return 100_bi;
		case Moves::Sandstorm: return none;
		case Moves::Giga_Drain: return 100_bi;
		case Moves::Endure: return none;
		case Moves::Charm: return 100_bi;
		case Moves::Rollout: return 90_bi;
		case Moves::False_Swipe: return 100_bi;
		case Moves::Swagger: return 90_bi;
		case Moves::Milk_Drink: return none;
		case Moves::Spark: return 100_bi;
		case Moves::Fury_Cutter: return 95_bi;
		case Moves::Steel_Wing: return 90_bi;
		case Moves::Mean_Look: return none;
		case Moves::Attract: return 100_bi;
		case Moves::Sleep_Talk: return none;
		case Moves::Heal_Bell: return none;
		case Moves::Return: return 100_bi;
		case Moves::Present: return 90_bi;
		case Moves::Frustration: return 100_bi;
		case Moves::Safeguard: return none;
		case Moves::Pain_Split: return none;
		case Moves::Sacred_Fire: return 95_bi;
		case Moves::Magnitude: return 100_bi;
		case Moves::DynamicPunch: return 50_bi;
		case Moves::Megahorn: return 85_bi;
		case Moves::DragonBreath: return 100_bi;
		case Moves::Baton_Pass: return none;
		case Moves::Encore: return 100_bi;
		case Moves::Pursuit: return 100_bi;
		case Moves::Rapid_Spin: return 100_bi;
		case Moves::Sweet_Scent: return 100_bi;
		case Moves::Iron_Tail: return 75_bi;
		case Moves::Metal_Claw: return 95_bi;
		case Moves::Vital_Throw: return none;
		case Moves::Morning_Sun: return none;
		case Moves::Synthesis: return none;
		case Moves::Moonlight: return none;
		case Moves::Hidden_Power: return 100_bi;
		case Moves::Cross_Chop: return 80_bi;
		case Moves::Twister: return 100_bi;
		case Moves::Rain_Dance: return none;
		case Moves::Sunny_Day: return none;
		case Moves::Crunch: return 100_bi;
		case Moves::Mirror_Coat: return 100_bi;
		case Moves::Psych_Up: return none;
		case Moves::ExtremeSpeed: return 100_bi;
		case Moves::AncientPower: return 100_bi;
		case Moves::Shadow_Ball: return 100_bi;
		case Moves::Future_Sight: return 100_bi;
		case Moves::Rock_Smash: return 100_bi;
		case Moves::Whirlpool: return 85_bi;
		case Moves::Beat_Up: return 100_bi;
		case Moves::Fake_Out: return 100_bi;
		case Moves::Uproar: return 100_bi;
		case Moves::Stockpile: return none;
		case Moves::Spit_Up: return 100_bi;
		case Moves::Swallow: return none;
		case Moves::Heat_Wave: return 90_bi;
		case Moves::Hail: return none;
		case Moves::Torment: return 100_bi;
		case Moves::Flatter: return 100_bi;
		case Moves::Will_O_Wisp: return 75_bi;
		case Moves::Memento: return 100_bi;
		case Moves::Facade: return 100_bi;
		case Moves::Focus_Punch: return 100_bi;
		case Moves::SmellingSalt: return 100_bi;
		case Moves::Follow_Me: return none;
		case Moves::Nature_Power: return none;
		case Moves::Charge: return none;
		case Moves::Taunt: return 100_bi;
		case Moves::Helping_Hand: return none;
		case Moves::Trick: return 100_bi;
		case Moves::Role_Play: return none;
		case Moves::Wish: return none;
		case Moves::Assist: return none;
		case Moves::Ingrain: return none;
		case Moves::Superpower: return 100_bi;
		case Moves::Magic_Coat: return none;
		case Moves::Recycle: return none;
		case Moves::Revenge: return 100_bi;
		case Moves::Brick_Break: return 100_bi;
		case Moves::Yawn: return none;
		case Moves::Knock_Off: return 100_bi;
		case Moves::Endeavor: return 100_bi;
		case Moves::Eruption: return 100_bi;
		case Moves::Skill_Swap: return none;
		case Moves::Imprison: return none;
		case Moves::Refresh: return none;
		case Moves::Grudge: return none;
		case Moves::Snatch: return none;
		case Moves::Secret_Power: return 100_bi;
		case Moves::Dive: return 100_bi;
		case Moves::Arm_Thrust: return 100_bi;
		case Moves::Camouflage: return none;
		case Moves::Tail_Glow: return none;
		case Moves::Luster_Purge: return 100_bi;
		case Moves::Mist_Ball: return 100_bi;
		case Moves::FeatherDance: return 100_bi;
		case Moves::Teeter_Dance: return 100_bi;
		case Moves::Blaze_Kick: return 90_bi;
		case Moves::Mud_Sport: return none;
		case Moves::Ice_Ball: return 90_bi;
		case Moves::Needle_Arm: return 100_bi;
		case Moves::Slack_Off: return none;
		case Moves::Hyper_Voice: return 100_bi;
		case Moves::Poison_Fang: return 100_bi;
		case Moves::Crush_Claw: return 95_bi;
		case Moves::Blast_Burn: return 90_bi;
		case Moves::Hydro_Cannon: return 90_bi;
		case Moves::Meteor_Mash: return 85_bi;
		case Moves::Astonish: return 100_bi;
		case Moves::Weather_Ball: return 100_bi;
		case Moves::Aromatherapy: return none;
		case Moves::Fake_Tears: return 100_bi;
		case Moves::Air_Cutter: return 95_bi;
		case Moves::Overheat: return 90_bi;
		case Moves::Odor_Sleuth: return none;
		case Moves::Rock_Tomb: return 80_bi;
		case Moves::Silver_Wind: return 100_bi;
		case Moves::Metal_Sound: return 85_bi;
		case Moves::GrassWhistle: return 55_bi;
		case Moves::Tickle: return 100_bi;
		case Moves::Cosmic_Power: return none;
		case Moves::Water_Spout: return 100_bi;
		case Moves::Signal_Beam: return 100_bi;
		case Moves::Shadow_Punch: return none;
		case Moves::Extrasensory: return 100_bi;
		case Moves::Sky_Uppercut: return 90_bi;
		case Moves::Sand_Tomb: return 85_bi;
		case Moves::Sheer_Cold: return 30_bi;
		case Moves::Muddy_Water: return 85_bi;
		case Moves::Bullet_Seed: return 100_bi;
		case Moves::Aerial_Ace: return none;
		case Moves::Icicle_Spear: return 100_bi;
		case Moves::Iron_Defense: return none;
		case Moves::Block: return none;
		case Moves::Howl: return none;
		case Moves::Dragon_Claw: return 100_bi;
		case Moves::Frenzy_Plant: return 90_bi;
		case Moves::Bulk_Up: return none;
		case Moves::Bounce: return 85_bi;
		case Moves::Mud_Shot: return 95_bi;
		case Moves::Poison_Tail: return 100_bi;
		case Moves::Covet: return 100_bi;
		case Moves::Volt_Tackle: return 100_bi;
		case Moves::Magical_Leaf: return none;
		case Moves::Water_Sport: return none;
		case Moves::Calm_Mind: return none;
		case Moves::Leaf_Blade: return 100_bi;
		case Moves::Dragon_Dance: return none;
		case Moves::Rock_Blast: return 90_bi;
		case Moves::Shock_Wave: return none;
		case Moves::Water_Pulse: return 100_bi;
		case Moves::Doom_Desire: return 100_bi;
		case Moves::Psycho_Boost: return 90_bi;
		case Moves::Roost: return none;
		case Moves::Gravity: return none;
		case Moves::Miracle_Eye: return none;
		case Moves::Wake_Up_Slap: return 100_bi;
		case Moves::Hammer_Arm: return 90_bi;
		case Moves::Gyro_Ball: return 100_bi;
		case Moves::Healing_Wish: return none;
		case Moves::Brine: return 100_bi;
		case Moves::Natural_Gift: return 100_bi;
		case Moves::Feint: return 100_bi;
		case Moves::Pluck: return 100_bi;
		case Moves::Tailwind: return none;
		case Moves::Acupressure: return none;
		case Moves::Metal_Burst: return 100_bi;
		case Moves::U_turn: return 100_bi;
		case Moves::Close_Combat: return 100_bi;
		case Moves::Payback: return 100_bi;
		case Moves::Assurance: return 100_bi;
		case Moves::Embargo: return 100_bi;
		case Moves::Fling: return 100_bi;
		case Moves::Psycho_Shift: return 90_bi;
		case Moves::Trump_Card: return none;
		case Moves::Heal_Block: return 100_bi;
		case Moves::Wring_Out: return 100_bi;
		case Moves::Power_Trick: return none;
		case Moves::Gastro_Acid: return 100_bi;
		case Moves::Lucky_Chant: return none;
		case Moves::Me_First: return none;
		case Moves::Copycat: return none;
		case Moves::Power_Swap: return none;
		case Moves::Guard_Swap: return none;
		case Moves::Punishment: return 100_bi;
		case Moves::Last_Resort: return 100_bi;
		case Moves::Worry_Seed: return 100_bi;
		case Moves::Sucker_Punch: return 100_bi;
		case Moves::Toxic_Spikes: return none;
		case Moves::Heart_Swap: return none;
		case Moves::Aqua_Ring: return none;
		case Moves::Magnet_Rise: return none;
		case Moves::Flare_Blitz: return 100_bi;
		case Moves::Force_Palm: return 100_bi;
		case Moves::Aura_Sphere: return none;
		case Moves::Rock_Polish: return none;
		case Moves::Poison_Jab: return 100_bi;
		case Moves::Dark_Pulse: return 100_bi;
		case Moves::Night_Slash: return 100_bi;
		case Moves::Aqua_Tail: return 90_bi;
		case Moves::Seed_Bomb: return 100_bi;
		case Moves::Air_Slash: return 95_bi;
		case Moves::X_Scissor: return 100_bi;
		case Moves::Bug_Buzz: return 100_bi;
		case Moves::Dragon_Pulse: return 100_bi;
		case Moves::Dragon_Rush: return 75_bi;
		case Moves::Power_Gem: return 100_bi;
		case Moves::Drain_Punch: return 100_bi;
		case Moves::Vacuum_Wave: return 100_bi;
		case Moves::Focus_Blast: return 70_bi;
		case Moves::Energy_Ball: return 100_bi;
		case Moves::Brave_Bird: return 100_bi;
		case Moves::Earth_Power: return 100_bi;
		case Moves::Switcheroo: return 100_bi;
		case Moves::Giga_Impact: return 90_bi;
		case Moves::Nasty_Plot: return none;
		case Moves::Bullet_Punch: return 100_bi;
		case Moves::Avalanche: return 100_bi;
		case Moves::Ice_Shard: return 100_bi;
		case Moves::Shadow_Claw: return 100_bi;
		case Moves::Thunder_Fang: return 95_bi;
		case Moves::Ice_Fang: return 95_bi;
		case Moves::Fire_Fang: return 95_bi;
		case Moves::Shadow_Sneak: return 100_bi;
		case Moves::Mud_Bomb: return 85_bi;
		case Moves::Psycho_Cut: return 100_bi;
		case Moves::Zen_Headbutt: return 90_bi;
		case Moves::Mirror_Shot: return 85_bi;
		case Moves::Flash_Cannon: return 100_bi;
		case Moves::Rock_Climb: return 85_bi;
		case Moves::Defog: return none;
		case Moves::Trick_Room: return none;
		case Moves::Draco_Meteor: return 90_bi;
		case Moves::Discharge: return 100_bi;
		case Moves::Lava_Plume: return 100_bi;
		case Moves::Leaf_Storm: return 90_bi;
		case Moves::Power_Whip: return 85_bi;
		case Moves::Rock_Wrecker: return 90_bi;
		case Moves::Cross_Poison: return 100_bi;
		case Moves::Gunk_Shot: return 70_bi;
		case Moves::Iron_Head: return 100_bi;
		case Moves::Magnet_Bomb: return none;
		case Moves::Stone_Edge: return 80_bi;
		case Moves::Captivate: return 100_bi;
		case Moves::Stealth_Rock: return none;
		case Moves::Grass_Knot: return 100_bi;
		case Moves::Chatter: return 100_bi;
		case Moves::Judgment: return 100_bi;
		case Moves::Bug_Bite: return 100_bi;
		case Moves::Charge_Beam: return 90_bi;
		case Moves::Wood_Hammer: return 100_bi;
		case Moves::Aqua_Jet: return 100_bi;
		case Moves::Attack_Order: return 100_bi;
		case Moves::Defend_Order: return none;
		case Moves::Heal_Order: return none;
		case Moves::Head_Smash: return 80_bi;
		case Moves::Double_Hit: return 90_bi;
		case Moves::Roar_of_Time: return 90_bi;
		case Moves::Spacial_Rend: return 95_bi;
		case Moves::Lunar_Dance: return none;
		case Moves::Crush_Grip: return 100_bi;
		case Moves::Magma_Storm: return 75_bi;
		case Moves::Dark_Void: return 80_bi;
		case Moves::Seed_Flare: return 85_bi;
		case Moves::Ominous_Wind: return 100_bi;
		case Moves::Shadow_Force: return 100_bi;
		case Moves::Hone_Claws: return none;
		case Moves::Wide_Guard: return none;
		case Moves::Guard_Split: return none;
		case Moves::Power_Split: return none;
		case Moves::Wonder_Room: return none;
		case Moves::Psyshock: return 100_bi;
		case Moves::Venoshock: return 100_bi;
		case Moves::Autotomize: return none;
		case Moves::Rage_Powder: return none;
		case Moves::Telekinesis: return none;
		case Moves::Magic_Room: return none;
		case Moves::Smack_Down: return 100_bi;
		case Moves::Storm_Throw: return 100_bi;
		case Moves::Flame_Burst: return 100_bi;
		case Moves::Sludge_Wave: return 100_bi;
		case Moves::Quiver_Dance: return none;
		case Moves::Heavy_Slam: return 100_bi;
		case Moves::Synchronoise: return 100_bi;
		case Moves::Electro_Ball: return 100_bi;
		case Moves::Soak: return 100_bi;
		case Moves::Flame_Charge: return 100_bi;
		case Moves::Coil: return none;
		case Moves::Low_Sweep: return 100_bi;
		case Moves::Acid_Spray: return 100_bi;
		case Moves::Foul_Play: return 100_bi;
		case Moves::Simple_Beam: return 100_bi;
		case Moves::Entrainment: return 100_bi;
		case Moves::After_You: return none;
		case Moves::Round: return 100_bi;
		case Moves::Echoed_Voice: return 100_bi;
		case Moves::Chip_Away: return 100_bi;
		case Moves::Clear_Smog: return none;
		case Moves::Stored_Power: return 100_bi;
		case Moves::Quick_Guard: return none;
		case Moves::Ally_Switch: return none;
		case Moves::Scald: return 100_bi;
		case Moves::Shell_Smash: return none;
		case Moves::Heal_Pulse: return none;
		case Moves::Hex: return 100_bi;
		case Moves::Sky_Drop: return 100_bi;
		case Moves::Shift_Gear: return none;
		case Moves::Circle_Throw: return 90_bi;
		case Moves::Incinerate: return 100_bi;
		case Moves::Quash: return 100_bi;
		case Moves::Acrobatics: return 100_bi;
		case Moves::Reflect_Type: return none;
		case Moves::Retaliate: return 100_bi;
		case Moves::Final_Gambit: return 100_bi;
		case Moves::Bestow: return none;
		case Moves::Inferno: return 50_bi;
		case Moves::Water_Pledge: return 100_bi;
		case Moves::Fire_Pledge: return 100_bi;
		case Moves::Grass_Pledge: return 100_bi;
		case Moves::Volt_Switch: return 100_bi;
		case Moves::Struggle_Bug: return 100_bi;
		case Moves::Bulldoze: return 100_bi;
		case Moves::Frost_Breath: return 90_bi;
		case Moves::Dragon_Tail: return 90_bi;
		case Moves::Work_Up: return none;
		case Moves::Electroweb: return 95_bi;
		case Moves::Wild_Charge: return 100_bi;
		case Moves::Drill_Run: return 95_bi;
		case Moves::Dual_Chop: return 90_bi;
		case Moves::Heart_Stamp: return 100_bi;
		case Moves::Horn_Leech: return 100_bi;
		case Moves::Sacred_Sword: return 100_bi;
		case Moves::Razor_Shell: return 95_bi;
		case Moves::Heat_Crash: return 100_bi;
		case Moves::Leaf_Tornado: return 90_bi;
		case Moves::Steamroller: return 100_bi;
		case Moves::Cotton_Guard: return none;
		case Moves::Night_Daze: return 95_bi;
		case Moves::Psystrike: return 100_bi;
		case Moves::Tail_Slap: return 85_bi;
		case Moves::Hurricane: return 70_bi;
		case Moves::Head_Charge: return 100_bi;
		case Moves::Gear_Grind: return 85_bi;
		case Moves::Searing_Shot: return 100_bi;
		case Moves::Techno_Blast: return 100_bi;
		case Moves::Relic_Song: return 100_bi;
		case Moves::Secret_Sword: return 100_bi;
		case Moves::Glaciate: return 95_bi;
		case Moves::Bolt_Strike: return 85_bi;
		case Moves::Blue_Flare: return 85_bi;
		case Moves::Fiery_Dance: return 100_bi;
		case Moves::Freeze_Shock: return 90_bi;
		case Moves::Ice_Burn: return 90_bi;
		case Moves::Snarl: return 95_bi;
		case Moves::Icicle_Crash: return 90_bi;
		case Moves::V_create: return 95_bi;
		case Moves::Fusion_Flare: return 100_bi;
		case Moves::Fusion_Bolt: return 100_bi;
		default: throw InvalidMove{};
	}
}

}	// namespace technicalmachine
