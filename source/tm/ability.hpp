// Copyright David Stone 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <bounded/integer.hpp>

#include <cstdint>

namespace technicalmachine {

enum class Generation : std::uint8_t;

enum class Ability : std::uint16_t {
	// Generation 3
	Stench,
	Drizzle,
	Speed_Boost,
	Battle_Armor,
	Sturdy,
	Damp,
	Limber,
	Sand_Veil,
	Static,
	Volt_Absorb,
	Water_Absorb,
	Oblivious,
	Cloud_Nine,
	Compound_Eyes,
	Insomnia,
	Color_Change,
	Immunity,
	Flash_Fire,
	Shield_Dust,
	Own_Tempo,
	Suction_Cups,
	Intimidate,
	Shadow_Tag,
	Rough_Skin,
	Wonder_Guard,
	Levitate,
	Effect_Spore,
	Synchronize,
	Clear_Body,
	Natural_Cure,
	Lightning_Rod,
	Serene_Grace,
	Swift_Swim,
	Chlorophyll,
	Illuminate,
	Trace,
	Huge_Power,
	Poison_Point,
	Inner_Focus,
	Magma_Armor,
	Water_Veil,
	Magnet_Pull,
	Soundproof,
	Rain_Dish,
	Sand_Stream,
	Pressure,
	Thick_Fat,
	Early_Bird,
	Flame_Body,
	Run_Away,
	Keen_Eye,
	Hyper_Cutter,
	Pickup,
	Truant,
	Hustle,
	Cute_Charm,
	Plus,
	Minus,
	Forecast,
	Sticky_Hold,
	Shed_Skin,
	Guts,
	Marvel_Scale,
	Liquid_Ooze,
	Overgrow,
	Blaze,
	Torrent,
	Swarm,
	Rock_Head,
	Drought,
	Arena_Trap,
	Vital_Spirit,
	White_Smoke,
	Pure_Power,
	Shell_Armor,
	Air_Lock,
	
	// Generation 4
	Tangled_Feet,
	Motor_Drive,
	Rivalry,
	Steadfast,
	Snow_Cloak,
	Gluttony,
	Anger_Point,
	Unburden,
	Heatproof,
	Simple,
	Dry_Skin,
	Download,
	Iron_Fist,
	Poison_Heal,
	Adaptability,
	Skill_Link,
	Hydration,
	Solar_Power,
	Quick_Feet,
	Normalize,
	Sniper,
	Magic_Guard,
	No_Guard,
	Stall,
	Technician,
	Leaf_Guard,
	Klutz,
	Mold_Breaker,
	Super_Luck,
	Aftermath,
	Anticipation,
	Forewarn,
	Unaware,
	Tinted_Lens,
	Filter,
	Slow_Start,
	Scrappy,
	Storm_Drain,
	Ice_Body,
	Solid_Rock,
	Snow_Warning,
	Honey_Gather,
	Frisk,
	Reckless,
	Multitype,
	Flower_Gift,
	Bad_Dreams,
	
	// Generation 5
	Pickpocket,
	Sheer_Force,
	Contrary,
	Unnerve,
	Defiant,
	Defeatist,
	Cursed_Body,
	Healer,
	Friend_Guard,
	Weak_Armor,
	Heavy_Metal,
	Light_Metal,
	Multiscale,
	Toxic_Boost,
	Flare_Boost,
	Harvest,
	Telepathy,
	Moody,
	Overcoat,
	Poison_Touch,
	Regenerator,
	Big_Pecks,
	Sand_Rush,
	Wonder_Skin,
	Analytic,
	Illusion,
	Imposter,
	Infiltrator,
	Mummy,
	Moxie,
	Justified,
	Rattled,
	Magic_Bounce,
	Sap_Sipper,
	Prankster,
	Sand_Force,
	Iron_Barbs,
	Zen_Mode,
	Victory_Star,
	Turboblaze,
	Teravolt,
	
	// Generation 6
	Aroma_Veil,
	Flower_Veil,
	Cheek_Pouch,
	Protean,
	Fur_Coat,
	Magician,
	Bulletproof,
	Competitive,
	Strong_Jaw,
	Refrigerate,
	Sweet_Veil,
	Stance_Change,
	Gale_Wings,
	Mega_Launcher,
	Grass_Pelt,
	Symbiosis,
	Tough_Claws,
	Pixilate,
	Gooey,
	Aerilate,
	Parental_Bond,
	Dark_Aura,
	Fairy_Aura,
	Aura_Break,
	Primordial_Sea,
	Desolate_Land,
	Delta_Stream,
	
	// Generation 7
	Stamina,
	Wimp_Out,
	Emergency_Exit,
	Water_Compaction,
	Merciless,
	Shields_Down,
	Stakeout,
	Water_Bubble,
	Steelworker,
	Berserk,
	Slush_Rush,
	Long_Reach,
	Liquid_Voice,
	Triage,
	Galvanize,
	Surge_Surfer,
	Schooling,
	Disguise,
	Battle_Bond,
	Power_Construct,
	Corrosion,
	Comatose,
	Queenly_Majesty,
	Innards_Out,
	Dancer,
	Battery,
	Fluffy,
	Dazzling,
	Soul_Heart,
	Tangling_Hair,
	Receiver,
	Power_of_Alchemy,
	Beast_Boost,
	RKS_System,
	Electric_Surge,
	Psychic_Surge,
	Misty_Surge,
	Grassy_Surge,
	Full_Metal_Body,
	Shadow_Shield,
	Prism_Armor,
	Neuroforce,
	
	// Generation 8
	Intrepid_Sword,
	Dauntless_Shield,
	Libero,
	Ball_Fetch,
	Cotton_Down,
	Propeller_Tail,
	Mirror_Armor,
	Gulp_Missile,
	Stalwart,
	Steam_Engine,
	Punk_Rock,
	Sand_Spit,
	Ice_Scales,
	Ripen,
	Ice_Face,
	Power_Spot,
	Mimicry,
	Screen_Cleaner,
	Steely_Spirit,
	Perish_Body,
	Wandering_Spirit,
	Gorilla_Tactics,
	Neutralizing_Gas,
	Pastel_Veil,
	Hunger_Switch,
};

} // namespace technicalmachine
namespace bounded {

template<>
inline constexpr auto min_value<technicalmachine::Ability> = technicalmachine::Ability();

template<>
inline constexpr auto max_value<technicalmachine::Ability> = technicalmachine::Ability::Hunger_Switch;

}	// namespace bounded
namespace technicalmachine {

constexpr bool blocks_confusion(Ability const ability) {
	return ability == Ability::Own_Tempo;
}

constexpr bool reflects_status(Ability const ability) {
	return ability == Ability::Synchronize;
}

constexpr bool absorbs_poison_damage(Ability const ability) {
	return ability == Ability::Poison_Heal;
}

constexpr bool blocks_burn_damage_penalty(Ability const ability) {
	return ability == Ability::Guts;
}

constexpr bool blocks_paralysis_speed_penalty(Ability const ability) {
	return ability == Ability::Quick_Feet;
}

constexpr bool blocks_sound_moves(Ability const ability) {
	return ability == Ability::Soundproof;
}

constexpr bool clears_status_on_switch(Ability const ability) {
	return ability == Ability::Natural_Cure;
}

constexpr bool is_immune_to_ground(Ability const ability) {
	return ability == Ability::Levitate;
}

constexpr bool wakes_up_early(Ability const ability) {
	return ability == Ability::Early_Bird;
}

constexpr bool weakens_burn(Ability const ability) {
	return ability == Ability::Heatproof;
}

constexpr bool harms_sleepers(Ability const ability) {
	return ability == Ability::Bad_Dreams;
}

constexpr bool blocks_phazing(Ability const ability) {
	return ability == Ability::Suction_Cups;
}

constexpr bool blocks_recoil(Ability const ability) {
	switch (ability) {
		case Ability::Magic_Guard:
		case Ability::Rock_Head:
			return true;
		default:
			return false;
	}
}

constexpr bool blocks_secondary_damage(Ability const ability) {
	return ability == Ability::Magic_Guard;
}

constexpr bool cannot_miss(Ability const ability) {
	return ability == Ability::No_Guard;
}

constexpr bool damages_leechers(Ability const ability) {
	return ability == Ability::Liquid_Ooze;
}

constexpr bool weakens_se_attacks(Ability const ability) {
	switch (ability) {
		case Ability::Filter:
		case Ability::Solid_Rock:
			return true;
		default:
			return false;
	}
}

constexpr bool strengthens_nve_attacks(Ability const ability) {
	return ability == Ability::Tinted_Lens;
}

constexpr bool uses_extra_pp(Ability const ability) {
	return ability == Ability::Pressure;
}

constexpr bool boosts_speed(Ability const ability) {
	return ability == Ability::Speed_Boost;
}

constexpr bool boosts_speed_when_flinched(Ability const ability) {
	return ability == Ability::Steadfast;
}

constexpr bool boosts_stab(Ability const ability) {
	return ability == Ability::Adaptability;
}

auto blocks_intimidate(Generation, Ability) -> bool;
auto traceable(Generation, Ability) -> bool;

}	// namespace technicalmachine
