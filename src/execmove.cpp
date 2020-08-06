#include "..\include\combat.h"
#include "..\include\move_impl.h"

//TODO: play the corresponding sounds
void CombatData::ExecMove(CasterTargetsPair &ctp){
	bool playedCasterAnim = false;
	for(auto &it : ctp.targets){
		if(it->remHP != 0){
			switch(ctp.move->id){
			case IGNITE:
				MoveImplementation::IGNITE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BLAZE:
				MoveImplementation::BLAZE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FIREBALL:
				MoveImplementation::FIREBALL(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case EXPLOSION:
				MoveImplementation::EXPLOSION(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FIREBEAM:
				MoveImplementation::FIREBEAM(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FLAMESWORD:
				MoveImplementation::FLAMESWORD(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FLAREKICK:
				MoveImplementation::FLAREKICK(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FIREWALL:
				MoveImplementation::FIREWALL(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SEARINGFLESH:
				MoveImplementation::SEARINGFLESH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case MOLTENMETEOR:
				MoveImplementation::MOLTENMETEOR(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case WILDFIRE:
				MoveImplementation::WILDFIRE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case RAZEEARTH:
				MoveImplementation::RAZEEARTH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FROMTHEASHES:
				MoveImplementation::FROMTHEASHES(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SUPERNOVA:
				MoveImplementation::SUPERNOVA(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case WATERWHIP:
				MoveImplementation::WATERWHIP(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case TORRENT:
				MoveImplementation::TORRENT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case TIDALWAVE:
				MoveImplementation::TIDALWAVE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case COALESCE:
				MoveImplementation::COALESCE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case WHIRLPOOL:
				MoveImplementation::WHIRLPOOL(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case HAILSTORM:
				MoveImplementation::HAILSTORM(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case AQUAPRISON:
				MoveImplementation::AQUAPRISON(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case RAINSTORM:
				MoveImplementation::RAINSTORM(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case DEWPOINT:
				MoveImplementation::DEWPOINT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FLASHFREEZE:
				MoveImplementation::FLASHFREEZE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case RIPTIDE:
				MoveImplementation::RIPTIDE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case VAPORVORTEX:
				MoveImplementation::VAPORVORTEX(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case HELLBROTH:
				MoveImplementation::HELLBROTH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case TSUNAMI:
				MoveImplementation::TSUNAMI(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SEEDSHOT:
				MoveImplementation::SEEDSHOT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ACORNASSAULT:
				MoveImplementation::ACORNASSAULT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SAPPINGSTEMS:
				MoveImplementation::SAPPINGSTEMS(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case NOURISH:
				MoveImplementation::NOURISH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case LEAFLANCE:
				MoveImplementation::LEAFLANCE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FUNGALSPORES:
				MoveImplementation::FUNGALSPORES(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BARBEDHUSK:
				MoveImplementation::BARBEDHUSK(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case GRASSBLADES:
				MoveImplementation::GRASSBLADES(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case PETALPIKE:
				MoveImplementation::PETALPIKE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case UNDERGROWTH:
				MoveImplementation::UNDERGROWTH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SYMBIOSIS:
				MoveImplementation::SYMBIOSIS(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ENSNARINGVINE:
				MoveImplementation::ENSNARINGVINE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case RANCIDROSES:
				MoveImplementation::RANCIDROSES(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case DRYADSCURSE:
				MoveImplementation::DRYADSCURSE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ZAP:
				MoveImplementation::ZAP(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CHARGE:
				MoveImplementation::CHARGE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case DISCHARGE:
				MoveImplementation::DISCHARGE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case LIGHTNINGBOLT:
				MoveImplementation::LIGHTNINGBOLT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case DAZZLINGLIGHTS:
				MoveImplementation::DAZZLINGLIGHTS(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ELECTROSTORM:
				MoveImplementation::ELECTROSTORM(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case LIGHTNINGKICK:
				MoveImplementation::LIGHTNINGKICK(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SPARKINGSKIN:
				MoveImplementation::SPARKINGSKIN(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SUPERCONDUCT:
				MoveImplementation::SUPERCONDUCT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case STATICSHOCK:
				MoveImplementation::STATICSHOCK(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case EVANESCENTFIELD:
				MoveImplementation::EVANESCENTFIELD(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case HIGHVOLTAGE:
				MoveImplementation::HIGHVOLTAGE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case MJOLNIR:
				MoveImplementation::MJOLNIR(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CLOSEDCIRUIT:
				MoveImplementation::CLOSEDCIRUIT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case IRONSPIKES:
				MoveImplementation::IRONSPIKES(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CANNONBALL:
				MoveImplementation::CANNONBALL(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SHARPEN:
				MoveImplementation::SHARPEN(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SHATTERSHRAPNEL:
				MoveImplementation::SHATTERSHRAPNEL(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BALLANDCHAIN:
				MoveImplementation::BALLANDCHAIN(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case QUICKSILVER:
				MoveImplementation::QUICKSILVER(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case COPPERCUTLASS:
				MoveImplementation::COPPERCUTLASS(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case RAZORWIRE:
				MoveImplementation::RAZORWIRE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case MIDASTOUCH:
				MoveImplementation::MIDASTOUCH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CHROMEPLATED:
				MoveImplementation::CHROMEPLATED(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case MAGNETIZE:
				MoveImplementation::MAGNETIZE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BRASSKNUCKLES:
				MoveImplementation::BRASSKNUCKLES(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ALLOYASSAULT:
				MoveImplementation::ALLOYASSAULT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case PIERCINGPLATINUM:
				MoveImplementation::PIERCINGPLATINUM(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case HURLROCK:
				MoveImplementation::HURLROCK(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case STONESPEAR:
				MoveImplementation::STONESPEAR(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FORTIFY:
				MoveImplementation::FORTIFY(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case QUICKSAND:
				MoveImplementation::QUICKSAND(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ENTOMB:
				MoveImplementation::ENTOMB(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CRUSH:
				MoveImplementation::CRUSH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case TREMOR:
				MoveImplementation::TREMOR(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ROCKSLIDE:
				MoveImplementation::ROCKSLIDE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ROLLINGBOULDER:
				MoveImplementation::ROLLINGBOULDER(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SAPPHIRESTRIKE:
				MoveImplementation::SAPPHIRESTRIKE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case RUBYRUSH:
				MoveImplementation::RUBYRUSH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case GARNETGAZE:
				MoveImplementation::GARNETGAZE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case EMERALDEDGE:
				MoveImplementation::EMERALDEDGE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case OBSIDIANONSLAUGHT:
				MoveImplementation::OBSIDIANONSLAUGHT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ECTORAY:
				MoveImplementation::ECTORAY(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case TORMENT:
				MoveImplementation::TORMENT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CHAOSCLAW:
				MoveImplementation::CHAOSCLAW(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case PHANTOMWALTS:
				MoveImplementation::PHANTOMWALTS(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case GRAVETENDER:
				MoveImplementation::GRAVETENDER(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case MINDINVASION:
				MoveImplementation::MINDINVASION(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BINDINGPAIN:
				MoveImplementation::BINDINGPAIN(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case PLAGUE:
				MoveImplementation::PLAGUE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case WICKEDHEX:
				MoveImplementation::WICKEDHEX(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case PETRIFYINGWAIL:
				MoveImplementation::PETRIFYINGWAIL(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case DECAY:
				MoveImplementation::DECAY(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case VIVIDNIGHTMARE:
				MoveImplementation::VIVIDNIGHTMARE(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ETHEREALFOG:
				MoveImplementation::ETHEREALFOG(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case NOXIOUSVOID:
				MoveImplementation::NOXIOUSVOID(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FLASHFRICTION:
				MoveImplementation::FLASHFRICTION(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SCORCHINGHEAT:
				MoveImplementation::SCORCHINGHEAT(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case DRAGONBREATH:
				MoveImplementation::DRAGONBREATH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ICARUSINFERNO:
				MoveImplementation::ICARUSINFERNO(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case REND:
				MoveImplementation::REND(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SIRENSTEAR:
				/* MoveImplementation::SIRENSTEAR(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CHILLINGBLAST:
				/* MoveImplementation::CHILLINGBLAST(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case DELUGE:
				/* MoveImplementation::DELUGE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case NEEDLE:
				/* MoveImplementation::NEEDLE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BLOOM:
				/* MoveImplementation::BLOOM(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case TREECLEAVER:
				/* MoveImplementation::TREECLEAVER(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case VENOMCOATING:
				/* MoveImplementation::VENOMCOATING(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SURGE:
				/* MoveImplementation::SURGE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case OVERLOAD:
				/* MoveImplementation::OVERLOAD(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case IONSTRIKE:
				/* MoveImplementation::IONSTRIKE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case PLASMAPULSE:
				/* MoveImplementation::PLASMAPULSE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SCRAPSLUG:
				/* MoveImplementation::SCRAPSLUG(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ANNEAL:
				/* MoveImplementation::ANNEAL(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case ANODIZE:
				/* MoveImplementation::ANODIZE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case GALVANIZEDGLAIVE:
				/* MoveImplementation::GALVANIZEDGLAIVE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case GRAVELSPIN:
				/* MoveImplementation::GRAVELSPIN(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SANDBOMB:
				/* MoveImplementation::SANDBOMB(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case CRYSTALCAGE:
				/* MoveImplementation::CRYSTALCAGE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case FISSURE:
				/* MoveImplementation::FISSURE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case SHADOWSLASH:
				MoveImplementation::SHADOWSLASH(*it, *static_cast<CasterMove *>(&ctp));
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case PILFER:
				/* MoveImplementation::PILFER(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Physical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BLOODCURDLE:
				/* MoveImplementation::BLOODCURDLE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
				break;
			case BLACKHOLE:
				/* MoveImplementation::BLACKHOLE(*it, *static_cast<CasterMove *>(&ctp)); */
				{
					if(!playedCasterAnim){
						actorSprites[ctp.caster].playAnimation("Use Magical", 
							[](){ animLockouts--; }
						);
						playedCasterAnim = true;
						animLockouts++;
					}
				}
				actorSprites[it].playAnimation("Hurt", 8, 
					[](){ animLockouts--; }
				);
				animLockouts++;
			default:
				break;
			}
		}
	}
	moveAnimPlaying = playedCasterAnim;
	return;
}

