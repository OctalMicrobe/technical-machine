// Copyright (C) 2015 David Stone
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

#include <tm/move/move.hpp>

#include <cstdint>

#include <tm/move/base_power.hpp>
#include <tm/move/is_switch.hpp>
#include <tm/move/moves.hpp>

namespace technicalmachine {

auto is_damaging(Moves const move) -> bool {
	auto const power = base_power(move);
	return !static_cast<bool>(power) or *power != 0_bi;
}

auto is_phaze(Moves const move) -> bool {
	switch (move) {
		case Moves::Roar:
		case Moves::Whirlwind:
			return true;
		default:
			return false;
	}
}

auto is_usable_while_frozen(Moves const move) -> bool {
	switch (move) {
		case Moves::Flame_Wheel:
		case Moves::Sacred_Fire:
			return true;
		default:
			return false;
	}
}

auto is_regular(Moves const move) -> bool {
	switch (move) {
		case Moves::Pass:
		case Moves::Hit_Self:
		case Moves::Struggle:
			return false;
		default:
			return !is_switch(move);
	}
}


namespace {

enum class MoveCategory { physical, special, other };

constexpr auto move_category(Moves const move) {
	switch (move) {
		case Moves::Hit_Self:
		case Moves::Pound:
		case Moves::Karate_Chop:
		case Moves::DoubleSlap:
		case Moves::Comet_Punch:
		case Moves::Mega_Punch:
		case Moves::Pay_Day:
		case Moves::Fire_Punch:
		case Moves::Ice_Punch:
		case Moves::ThunderPunch:
		case Moves::Scratch:
		case Moves::ViceGrip:
		case Moves::Guillotine:
		case Moves::Cut:
		case Moves::Wing_Attack:
		case Moves::Fly:
		case Moves::Bind:
		case Moves::Slam:
		case Moves::Vine_Whip:
		case Moves::Stomp:
		case Moves::Double_Kick:
		case Moves::Mega_Kick:
		case Moves::Jump_Kick:
		case Moves::Rolling_Kick:
		case Moves::Headbutt:
		case Moves::Horn_Attack:
		case Moves::Fury_Attack:
		case Moves::Horn_Drill:
		case Moves::Tackle:
		case Moves::Body_Slam:
		case Moves::Wrap:
		case Moves::Take_Down:
		case Moves::Thrash:
		case Moves::Double_Edge:
		case Moves::Poison_Sting:
		case Moves::Twineedle:
		case Moves::Pin_Missile:
		case Moves::Bite:
		case Moves::Peck:
		case Moves::Drill_Peck:
		case Moves::Submission:
		case Moves::Low_Kick:
		case Moves::Counter:
		case Moves::Seismic_Toss:
		case Moves::Strength:
		case Moves::Razor_Leaf:
		case Moves::Rock_Throw:
		case Moves::Earthquake:
		case Moves::Fissure:
		case Moves::Dig:
		case Moves::Quick_Attack:
		case Moves::Rage:
		case Moves::Bide:
		case Moves::Selfdestruct:
		case Moves::Egg_Bomb:
		case Moves::Lick:
		case Moves::Bone_Club:
		case Moves::Waterfall:
		case Moves::Clamp:
		case Moves::Skull_Bash:
		case Moves::Spike_Cannon:
		case Moves::Constrict:
		case Moves::Hi_Jump_Kick:
		case Moves::Barrage:
		case Moves::Leech_Life:
		case Moves::Sky_Attack:
		case Moves::Dizzy_Punch:
		case Moves::Crabhammer:
		case Moves::Explosion:
		case Moves::Fury_Swipes:
		case Moves::Bonemerang:
		case Moves::Rock_Slide:
		case Moves::Hyper_Fang:
		case Moves::Super_Fang:
		case Moves::Slash:
		case Moves::Struggle:
		case Moves::Triple_Kick:
		case Moves::Thief:
		case Moves::Flame_Wheel:
		case Moves::Flail:
		case Moves::Reversal:
		case Moves::Mach_Punch:
		case Moves::Faint_Attack:
		case Moves::Bone_Rush:
		case Moves::Outrage:
		case Moves::Rollout:
		case Moves::False_Swipe:
		case Moves::Spark:
		case Moves::Fury_Cutter:
		case Moves::Steel_Wing:
		case Moves::Return:
		case Moves::Present:
		case Moves::Frustration:
		case Moves::Sacred_Fire:
		case Moves::Magnitude:
		case Moves::DynamicPunch:
		case Moves::Megahorn:
		case Moves::Pursuit:
		case Moves::Rapid_Spin:
		case Moves::Iron_Tail:
		case Moves::Metal_Claw:
		case Moves::Vital_Throw:
		case Moves::Cross_Chop:
		case Moves::Crunch:
		case Moves::ExtremeSpeed:
		case Moves::Rock_Smash:
		case Moves::Beat_Up:
		case Moves::Fake_Out:
		case Moves::Facade:
		case Moves::Focus_Punch:
		case Moves::SmellingSalt:
		case Moves::Superpower:
		case Moves::Revenge:
		case Moves::Brick_Break:
		case Moves::Knock_Off:
		case Moves::Endeavor:
		case Moves::Secret_Power:
		case Moves::Dive:
		case Moves::Arm_Thrust:
		case Moves::Blaze_Kick:
		case Moves::Ice_Ball:
		case Moves::Needle_Arm:
		case Moves::Poison_Fang:
		case Moves::Crush_Claw:
		case Moves::Meteor_Mash:
		case Moves::Astonish:
		case Moves::Rock_Tomb:
		case Moves::Shadow_Punch:
		case Moves::Sky_Uppercut:
		case Moves::Sand_Tomb:
		case Moves::Bullet_Seed:
		case Moves::Aerial_Ace:
		case Moves::Icicle_Spear:
		case Moves::Dragon_Claw:
		case Moves::Bounce:
		case Moves::Poison_Tail:
		case Moves::Covet:
		case Moves::Volt_Tackle:
		case Moves::Leaf_Blade:
		case Moves::Rock_Blast:
		case Moves::Wake_Up_Slap:
		case Moves::Hammer_Arm:
		case Moves::Gyro_Ball:
		case Moves::Natural_Gift:
		case Moves::Feint:
		case Moves::Pluck:
		case Moves::Metal_Burst:
		case Moves::U_turn:
		case Moves::Close_Combat:
		case Moves::Payback:
		case Moves::Assurance:
		case Moves::Fling:
		case Moves::Punishment:
		case Moves::Last_Resort:
		case Moves::Sucker_Punch:
		case Moves::Flare_Blitz:
		case Moves::Force_Palm:
		case Moves::Poison_Jab:
		case Moves::Night_Slash:
		case Moves::Aqua_Tail:
		case Moves::Seed_Bomb:
		case Moves::X_Scissor:
		case Moves::Dragon_Rush:
		case Moves::Drain_Punch:
		case Moves::Brave_Bird:
		case Moves::Giga_Impact:
		case Moves::Bullet_Punch:
		case Moves::Avalanche:
		case Moves::Ice_Shard:
		case Moves::Shadow_Claw:
		case Moves::Thunder_Fang:
		case Moves::Ice_Fang:
		case Moves::Fire_Fang:
		case Moves::Shadow_Sneak:
		case Moves::Psycho_Cut:
		case Moves::Zen_Headbutt:
		case Moves::Rock_Climb:
		case Moves::Power_Whip:
		case Moves::Rock_Wrecker:
		case Moves::Cross_Poison:
		case Moves::Gunk_Shot:
		case Moves::Iron_Head:
		case Moves::Magnet_Bomb:
		case Moves::Stone_Edge:
		case Moves::Bug_Bite:
		case Moves::Wood_Hammer:
		case Moves::Aqua_Jet:
		case Moves::Attack_Order:
		case Moves::Head_Smash:
		case Moves::Double_Hit:
		case Moves::Crush_Grip:
		case Moves::Shadow_Force:
		case Moves::Smack_Down:
		case Moves::Storm_Throw:
		case Moves::Heavy_Slam:
		case Moves::Flame_Charge:
		case Moves::Low_Sweep:
		case Moves::Foul_Play:
		case Moves::Chip_Away:
		case Moves::Sky_Drop:
		case Moves::Circle_Throw:
		case Moves::Acrobatics:
		case Moves::Retaliate:
		case Moves::Bulldoze:
		case Moves::Dragon_Tail:
		case Moves::Wild_Charge:
		case Moves::Drill_Run:
		case Moves::Dual_Chop:
		case Moves::Heart_Stamp:
		case Moves::Horn_Leech:
		case Moves::Sacred_Sword:
		case Moves::Razor_Shell:
		case Moves::Heat_Crash:
		case Moves::Steamroller:
		case Moves::Tail_Slap:
		case Moves::Head_Charge:
		case Moves::Gear_Grind:
		case Moves::Bolt_Strike:
		case Moves::Freeze_Shock:
		case Moves::Icicle_Crash:
		case Moves::V_create:
		case Moves::Fusion_Bolt:
			return MoveCategory::physical;
		case Moves::Razor_Wind:
		case Moves::Gust:
		case Moves::SonicBoom:
		case Moves::Acid:
		case Moves::Ember:
		case Moves::Flamethrower:
		case Moves::Water_Gun:
		case Moves::Hydro_Pump:
		case Moves::Surf:
		case Moves::Ice_Beam:
		case Moves::Blizzard:
		case Moves::Psybeam:
		case Moves::BubbleBeam:
		case Moves::Aurora_Beam:
		case Moves::Hyper_Beam:
		case Moves::Absorb:
		case Moves::Mega_Drain:
		case Moves::SolarBeam:
		case Moves::Petal_Dance:
		case Moves::Dragon_Rage:
		case Moves::Fire_Spin:
		case Moves::ThunderShock:
		case Moves::Thunderbolt:
		case Moves::Thunder:
		case Moves::Confusion:
		case Moves::Psychic:
		case Moves::Night_Shade:
		case Moves::Smog:
		case Moves::Sludge:
		case Moves::Fire_Blast:
		case Moves::Swift:
		case Moves::Dream_Eater:
		case Moves::Bubble:
		case Moves::Psywave:
		case Moves::Tri_Attack:
		case Moves::Snore:
		case Moves::Aeroblast:
		case Moves::Powder_Snow:
		case Moves::Sludge_Bomb:
		case Moves::Mud_Slap:
		case Moves::Octazooka:
		case Moves::Zap_Cannon:
		case Moves::Icy_Wind:
		case Moves::Giga_Drain:
		case Moves::DragonBreath:
		case Moves::Hidden_Power:
		case Moves::Twister:
		case Moves::Mirror_Coat:
		case Moves::AncientPower:
		case Moves::Shadow_Ball:
		case Moves::Future_Sight:
		case Moves::Whirlpool:
		case Moves::Uproar:
		case Moves::Spit_Up:
		case Moves::Heat_Wave:
		case Moves::Eruption:
		case Moves::Luster_Purge:
		case Moves::Mist_Ball:
		case Moves::Hyper_Voice:
		case Moves::Blast_Burn:
		case Moves::Hydro_Cannon:
		case Moves::Weather_Ball:
		case Moves::Air_Cutter:
		case Moves::Overheat:
		case Moves::Silver_Wind:
		case Moves::Water_Spout:
		case Moves::Signal_Beam:
		case Moves::Extrasensory:
		case Moves::Sheer_Cold:
		case Moves::Muddy_Water:
		case Moves::Frenzy_Plant:
		case Moves::Mud_Shot:
		case Moves::Magical_Leaf:
		case Moves::Shock_Wave:
		case Moves::Water_Pulse:
		case Moves::Doom_Desire:
		case Moves::Psycho_Boost:
		case Moves::Brine:
		case Moves::Trump_Card:
		case Moves::Wring_Out:
		case Moves::Aura_Sphere:
		case Moves::Dark_Pulse:
		case Moves::Air_Slash:
		case Moves::Bug_Buzz:
		case Moves::Dragon_Pulse:
		case Moves::Power_Gem:
		case Moves::Vacuum_Wave:
		case Moves::Focus_Blast:
		case Moves::Energy_Ball:
		case Moves::Earth_Power:
		case Moves::Mud_Bomb:
		case Moves::Mirror_Shot:
		case Moves::Flash_Cannon:
		case Moves::Draco_Meteor:
		case Moves::Discharge:
		case Moves::Lava_Plume:
		case Moves::Leaf_Storm:
		case Moves::Grass_Knot:
		case Moves::Chatter:
		case Moves::Judgment:
		case Moves::Charge_Beam:
		case Moves::Roar_of_Time:
		case Moves::Spacial_Rend:
		case Moves::Magma_Storm:
		case Moves::Seed_Flare:
		case Moves::Ominous_Wind:
		case Moves::Psyshock:
		case Moves::Venoshock:
		case Moves::Flame_Burst:
		case Moves::Sludge_Wave:
		case Moves::Synchronoise:
		case Moves::Electro_Ball:
		case Moves::Acid_Spray:
		case Moves::Round:
		case Moves::Echoed_Voice:
		case Moves::Clear_Smog:
		case Moves::Stored_Power:
		case Moves::Scald:
		case Moves::Hex:
		case Moves::Incinerate:
		case Moves::Final_Gambit:
		case Moves::Inferno:
		case Moves::Water_Pledge:
		case Moves::Fire_Pledge:
		case Moves::Grass_Pledge:
		case Moves::Volt_Switch:
		case Moves::Struggle_Bug:
		case Moves::Frost_Breath:
		case Moves::Electroweb:
		case Moves::Leaf_Tornado:
		case Moves::Night_Daze:
		case Moves::Psystrike:
		case Moves::Hurricane:
		case Moves::Searing_Shot:
		case Moves::Techno_Blast:
		case Moves::Relic_Song:
		case Moves::Secret_Sword:
		case Moves::Glaciate:
		case Moves::Blue_Flare:
		case Moves::Fiery_Dance:
		case Moves::Ice_Burn:
		case Moves::Snarl:
		case Moves::Fusion_Flare:
			return MoveCategory::special;
		case Moves::Pass:
		case Moves::Switch0:
		case Moves::Switch1:
		case Moves::Switch2:
		case Moves::Switch3:
		case Moves::Switch4:
		case Moves::Switch5:
		case Moves::Swords_Dance:
		case Moves::Whirlwind:
		case Moves::Sand_Attack:
		case Moves::Tail_Whip:
		case Moves::Leer:
		case Moves::Growl:
		case Moves::Roar:
		case Moves::Sing:
		case Moves::Supersonic:
		case Moves::Disable:
		case Moves::Mist:
		case Moves::Leech_Seed:
		case Moves::Growth:
		case Moves::PoisonPowder:
		case Moves::Stun_Spore:
		case Moves::Sleep_Powder:
		case Moves::String_Shot:
		case Moves::Thunder_Wave:
		case Moves::Toxic:
		case Moves::Hypnosis:
		case Moves::Meditate:
		case Moves::Agility:
		case Moves::Teleport:
		case Moves::Mimic:
		case Moves::Screech:
		case Moves::Double_Team:
		case Moves::Recover:
		case Moves::Harden:
		case Moves::Minimize:
		case Moves::SmokeScreen:
		case Moves::Confuse_Ray:
		case Moves::Withdraw:
		case Moves::Defense_Curl:
		case Moves::Barrier:
		case Moves::Light_Screen:
		case Moves::Haze:
		case Moves::Reflect:
		case Moves::Focus_Energy:
		case Moves::Metronome:
		case Moves::Mirror_Move:
		case Moves::Amnesia:
		case Moves::Kinesis:
		case Moves::Softboiled:
		case Moves::Glare:
		case Moves::Poison_Gas:
		case Moves::Lovely_Kiss:
		case Moves::Transform:
		case Moves::Spore:
		case Moves::Flash:
		case Moves::Splash:
		case Moves::Acid_Armor:
		case Moves::Rest:
		case Moves::Sharpen:
		case Moves::Conversion:
		case Moves::Substitute:
		case Moves::Sketch:
		case Moves::Spider_Web:
		case Moves::Mind_Reader:
		case Moves::Nightmare:
		case Moves::Curse:
		case Moves::Conversion_2:
		case Moves::Cotton_Spore:
		case Moves::Spite:
		case Moves::Protect:
		case Moves::Scary_Face:
		case Moves::Sweet_Kiss:
		case Moves::Belly_Drum:
		case Moves::Spikes:
		case Moves::Foresight:
		case Moves::Destiny_Bond:
		case Moves::Perish_Song:
		case Moves::Detect:
		case Moves::Lock_On:
		case Moves::Sandstorm:
		case Moves::Endure:
		case Moves::Charm:
		case Moves::Swagger:
		case Moves::Milk_Drink:
		case Moves::Mean_Look:
		case Moves::Attract:
		case Moves::Sleep_Talk:
		case Moves::Heal_Bell:
		case Moves::Safeguard:
		case Moves::Pain_Split:
		case Moves::Baton_Pass:
		case Moves::Encore:
		case Moves::Sweet_Scent:
		case Moves::Morning_Sun:
		case Moves::Synthesis:
		case Moves::Moonlight:
		case Moves::Rain_Dance:
		case Moves::Sunny_Day:
		case Moves::Psych_Up:
		case Moves::Stockpile:
		case Moves::Swallow:
		case Moves::Hail:
		case Moves::Torment:
		case Moves::Flatter:
		case Moves::Will_O_Wisp:
		case Moves::Memento:
		case Moves::Follow_Me:
		case Moves::Nature_Power:
		case Moves::Charge:
		case Moves::Taunt:
		case Moves::Helping_Hand:
		case Moves::Trick:
		case Moves::Role_Play:
		case Moves::Wish:
		case Moves::Assist:
		case Moves::Ingrain:
		case Moves::Magic_Coat:
		case Moves::Recycle:
		case Moves::Yawn:
		case Moves::Skill_Swap:
		case Moves::Imprison:
		case Moves::Refresh:
		case Moves::Grudge:
		case Moves::Snatch:
		case Moves::Camouflage:
		case Moves::Tail_Glow:
		case Moves::FeatherDance:
		case Moves::Teeter_Dance:
		case Moves::Mud_Sport:
		case Moves::Slack_Off:
		case Moves::Aromatherapy:
		case Moves::Fake_Tears:
		case Moves::Odor_Sleuth:
		case Moves::Metal_Sound:
		case Moves::GrassWhistle:
		case Moves::Tickle:
		case Moves::Cosmic_Power:
		case Moves::Iron_Defense:
		case Moves::Block:
		case Moves::Howl:
		case Moves::Bulk_Up:
		case Moves::Water_Sport:
		case Moves::Calm_Mind:
		case Moves::Dragon_Dance:
		case Moves::Roost:
		case Moves::Gravity:
		case Moves::Miracle_Eye:
		case Moves::Healing_Wish:
		case Moves::Tailwind:
		case Moves::Acupressure:
		case Moves::Embargo:
		case Moves::Psycho_Shift:
		case Moves::Heal_Block:
		case Moves::Power_Trick:
		case Moves::Gastro_Acid:
		case Moves::Lucky_Chant:
		case Moves::Me_First:
		case Moves::Copycat:
		case Moves::Power_Swap:
		case Moves::Guard_Swap:
		case Moves::Worry_Seed:
		case Moves::Toxic_Spikes:
		case Moves::Heart_Swap:
		case Moves::Aqua_Ring:
		case Moves::Magnet_Rise:
		case Moves::Rock_Polish:
		case Moves::Switcheroo:
		case Moves::Nasty_Plot:
		case Moves::Defog:
		case Moves::Trick_Room:
		case Moves::Captivate:
		case Moves::Stealth_Rock:
		case Moves::Defend_Order:
		case Moves::Heal_Order:
		case Moves::Lunar_Dance:
		case Moves::Dark_Void:
		case Moves::Hone_Claws:
		case Moves::Wide_Guard:
		case Moves::Guard_Split:
		case Moves::Power_Split:
		case Moves::Wonder_Room:
		case Moves::Autotomize:
		case Moves::Rage_Powder:
		case Moves::Telekinesis:
		case Moves::Magic_Room:
		case Moves::Quiver_Dance:
		case Moves::Soak:
		case Moves::Coil:
		case Moves::Simple_Beam:
		case Moves::Entrainment:
		case Moves::After_You:
		case Moves::Quick_Guard:
		case Moves::Ally_Switch:
		case Moves::Shell_Smash:
		case Moves::Heal_Pulse:
		case Moves::Shift_Gear:
		case Moves::Quash:
		case Moves::Reflect_Type:
		case Moves::Bestow:
		case Moves::Work_Up:
		case Moves::Cotton_Guard:
			return MoveCategory::other;
	}
}

} // namespace


auto is_physical(Moves const move) -> bool {
	return move_category(move) == MoveCategory::physical;
}

auto is_special(Moves const move) -> bool {
	return move_category(move) == MoveCategory::special;
}

}	// namespace technicalmachine
