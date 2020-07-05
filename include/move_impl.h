#pragma once
#ifndef MOVE_IMPL_H
#define MOVE_IMPL_H

#include <vector>

#include "moveeffect.h"

template<typename T>
using Vec = std::vector<T>;

struct Actor;
struct CasterMove;
struct Move;

//-
inline EffectDiff *AllocEDiff();

//-
inline EffectDiff *AllocEDiff(size_t);

namespace MoveImplementation{
	void IGNITE(Actor &, CasterMove &);
	void BLAZE(Actor &, CasterMove &);
	void FIREBALL(Actor &, CasterMove &);
	void EXPLOSION(Actor &, CasterMove &);
	void FIREBEAM(Actor &, CasterMove &);
	void FLAMESWORD(Actor &, CasterMove &);
	void FLAREKICK(Actor &, CasterMove &);
	void FIREWALL(Actor &, CasterMove &);
	void SEARINGFLESH(Actor &, CasterMove &);
	void MOLTENMETEOR(Actor &, CasterMove &);
	void WILDFIRE(Actor &, CasterMove &);
	void RAZEEARTH(Actor &, CasterMove &);
	void FROMTHEASHES(Actor &, CasterMove &);
	void SUPERNOVA(Actor &, CasterMove &);
	void WATERWHIP(Actor &, CasterMove &);
	void TORRENT(Actor &, CasterMove &);
	void TIDALWAVE(Actor &, CasterMove &);
	void COALESCE(Actor &, CasterMove &);
	void WHIRLPOOL(Actor &, CasterMove &);
	void HAILSTORM(Actor &, CasterMove &);
	void AQUAPRISON(Actor &, CasterMove &);
	void RAINSTORM(Actor &, CasterMove &);
	void DEWPOINT(Actor &, CasterMove &);
	void FLASHFREEZE(Actor &, CasterMove &);
	void RIPTIDE(Actor &, CasterMove &);
	void VAPORVORTEX(Actor &, CasterMove &);
	void HELLBROTH(Actor &, CasterMove &);
	void TSUNAMI(Actor &, CasterMove &);
	void SEEDSHOT(Actor &, CasterMove &);
	void ACORNASSAULT(Actor &, CasterMove &);
	void SAPPINGSTEMS(Actor &, CasterMove &);
	void NOURISH(Actor &, CasterMove &);
	void LEAFLANCE(Actor &, CasterMove &);
	void FUNGALSPORES(Actor &, CasterMove &);
	void BARBEDHUSK(Actor &, CasterMove &);
	void GRASSBLADES(Actor &, CasterMove &);
	void PETALPIKE(Actor &, CasterMove &);
	void UNDERGROWTH(Actor &, CasterMove &);
	void SYMBIOSIS(Actor &, CasterMove &);
	void ENSNARINGVINE(Actor &, CasterMove &);
	void RANCIDROSES(Actor &, CasterMove &);
	void DRYADSCURSE(Actor &, CasterMove &);
	void ZAP(Actor &, CasterMove &);
	void CHARGE(Actor &, CasterMove &);
	void DISCHARGE(Actor &, CasterMove &);
	void LIGHTNINGBOLT(Actor &, CasterMove &);
	void DAZZLINGLIGHTS(Actor &, CasterMove &);
	void ELECTROSTORM(Actor &, CasterMove &);
	void LIGHTNINGKICK(Actor &, CasterMove &);
	void SPARKINGSKIN(Actor &, CasterMove &);
	void SUPERCONDUCT(Actor &, CasterMove &);
	void STATICSHOCK(Actor &, CasterMove &);
	void EVANESCENTFIELD(Actor &, CasterMove &);
	void HIGHVOLTAGE(Actor &, CasterMove &);
	void MJOLNIR(Actor &, CasterMove &);
	void CLOSEDCIRUIT(Actor &, CasterMove &);
	void IRONSPIKES(Actor &, CasterMove &);
	void CANNONBALL(Actor &, CasterMove &);
	void SHARPEN(Actor &, CasterMove &);
	void SHATTERSHRAPNEL(Actor &, CasterMove &);
	void BALLANDCHAIN(Actor &, CasterMove &);
	void QUICKSILVER(Actor &, CasterMove &);
	void COPPERCUTLASS(Actor &, CasterMove &);
	void RAZORWIRE(Actor &, CasterMove &);
	void MIDASTOUCH(Actor &, CasterMove &);
	void CHROMEPLATED(Actor &, CasterMove &);
	void MAGNETIZE(Actor &, CasterMove &);
	void BRASSKNUCKLES(Actor &, CasterMove &);
	void ALLOYASSAULT(Actor &, CasterMove &);
	void PIERCINGPLATINUM(Actor &, CasterMove &);
	void HURLROCK(Actor &, CasterMove &);
	void STONESPEAR(Actor &, CasterMove &);
	void FORTIFY(Actor &, CasterMove &);
	void QUICKSAND(Actor &, CasterMove &);
	void ENTOMB(Actor &, CasterMove &);
	void CRUSH(Actor &, CasterMove &);
	void TREMOR(Actor &, CasterMove &);
	void ROCKSLIDE(Actor &, CasterMove &);
	void ROLLINGBOULDER(Actor &, CasterMove &);
	void SAPPHIRESTRIKE(Actor &, CasterMove &);
	void RUBYRUSH(Actor &, CasterMove &);
	void GARNETGAZE(Actor &, CasterMove &);
	void EMERALDEDGE(Actor &, CasterMove &);
	void OBSIDIANONSLAUGHT(Actor &, CasterMove &);
	void ECTORAY(Actor &, CasterMove &);
	void TORMENT(Actor &, CasterMove &);
	void CHAOSCLAW(Actor &, CasterMove &);
	void PHANTOMWALTS(Actor &, CasterMove &);
	void GRAVETENDER(Actor &, CasterMove &);
	void MINDINVASION(Actor &, CasterMove &);
	void BINDINGPAIN(Actor &, CasterMove &);
	void PLAGUE(Actor &, CasterMove &);
	void WICKEDHEX(Actor &, CasterMove &);
	void PETRIFYINGWAIL(Actor &, CasterMove &);
	void DECAY(Actor &, CasterMove &);
	void VIVIDNIGHTMARE(Actor &, CasterMove &);
	void ETHEREALFOG(Actor &, CasterMove &);
	void NOXIOUSVOID(Actor &, CasterMove &);
	void FLASHFRICTION(Actor &, CasterMove &);
	void SCORCHINGHEAT(Actor &, CasterMove &);
	void DRAGONBREATH(Actor &, CasterMove &);
	void ICARUSINFERNO(Actor &, CasterMove &);
	void REND(Actor &, CasterMove &);
	void SIRENSTEAR(Actor &, CasterMove &);
	void CHILLINGBLAST(Actor &, CasterMove &);
	void DELUGE(Actor &, CasterMove &);
	void NEEDLE(Actor &, CasterMove &);
	void BLOOM(Actor &, CasterMove &);
	void TREECLEAVER(Actor &, CasterMove &);
	void VENOMCOATING(Actor &, CasterMove &);
	void SURGE(Actor &, CasterMove &);
	void OVERLOAD(Actor &, CasterMove &);
	void IONSTRIKE(Actor &, CasterMove &);
	void PLASMAPULSE(Actor &, CasterMove &);
	void SCRAPSLUG(Actor &, CasterMove &);
	void ANNEAL(Actor &, CasterMove &);
	void ANODIZE(Actor &, CasterMove &);
	void GALVANIZEDGLAIVE(Actor &, CasterMove &);
	void GRAVELSPIN(Actor &, CasterMove &);
	void SANDBOMB(Actor &, CasterMove &);
	void CRYSTALCAGE(Actor &, CasterMove &);
	void FISSURE(Actor &, CasterMove &);
	void SHADOWSLASH(Actor &, CasterMove &);
	void PILFER(Actor &, CasterMove &);
	void BLOODCURDLE(Actor &, CasterMove &);
	void BLACKHOLE(Actor &, CasterMove &);
	
}


void ApplyDamage(Actor &, CasterMove &);

void ApplyHeal(Actor &, CasterMove &);


#endif

