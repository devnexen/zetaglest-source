// ==============================================================
//      This file is part of Glest (www.glest.org)
//
//      Copyright (C) 2001-2008 Martiño Figueroa
//
//      You can redistribute this code and/or modify it under
//      the terms of the GNU General Public License as published
//      by the Free Software Foundation; either version 2 of the
//      License, or (at your option) any later version
// ==============================================================

#ifndef _GLEST_GAME_FACTIONTYPE_H_
#   define _GLEST_GAME_FACTIONTYPE_H_

#   ifdef WIN32
#      include <winsock2.h>
#      include <winsock.h>
#   endif

#   include "unit_type.h"
#   include "upgrade_type.h"
#   include "sound.h"
#   include <map>
#   include <string>
#   include "util.h"
#   include "leak_dumper.h"

using Shared::Sound::StrSound;

namespace Glest
{
  namespace Game
  {
// =====================================================
//      class FactionType
//
///     Each of the possible factions the user can select
// =====================================================

    enum AIBehaviorUnitCategory
    {
      aibcWorkerUnits,
      aibcWarriorUnits,
      aibcResourceProducerUnits,
      aibcBuildingUnits
    };

    enum AIBehaviorStaticValueCategory
    {
      aibsvcMaxBuildRadius,
      aibsvcMinMinWarriors,
      aibsvcMinMinWarriorsExpandCpuEasy,
      aibsvcMinMinWarriorsExpandCpuMega,
      aibsvcMinMinWarriorsExpandCpuUltra,
      aibsvcMinMinWarriorsExpandCpuNormal,
      aibsvcMaxMinWarriors,
      aibsvcMaxExpansions,
      aibsvcVillageRadius,
      aibsvcMinStaticResourceCount,
      aibsvcScoutResourceRange,
      aibsvcMinWorkerAttackersHarvesting,
      aibsvcMinBuildSpacing
    };
    template <>
      inline EnumParser < AIBehaviorStaticValueCategory >::EnumParser ()
    {
      enumMap["MaxBuildRadius"] = aibsvcMaxBuildRadius;
      enumMap["MinMinWarriors"] = aibsvcMinMinWarriors;
      enumMap["MinMinWarriorsExpandCpuEasy"] =
        aibsvcMinMinWarriorsExpandCpuEasy;
      enumMap["MinMinWarriorsExpandCpuMega"] =
        aibsvcMinMinWarriorsExpandCpuMega;
      enumMap["MinMinWarriorsExpandCpuUltra"] =
        aibsvcMinMinWarriorsExpandCpuUltra;
      enumMap["MinMinWarriorsExpandCpuNormal"] =
        aibsvcMinMinWarriorsExpandCpuNormal;
      enumMap["MaxMinWarriors"] = aibsvcMaxMinWarriors;
      enumMap["MaxExpansions"] = aibsvcMaxExpansions;
      enumMap["VillageRadius"] = aibsvcVillageRadius;
      enumMap["MinStaticResourceCount"] = aibsvcMinStaticResourceCount;
      enumMap["ScoutResourceRange"] = aibsvcScoutResourceRange;
      enumMap["MinWorkerAttackersHarvesting"] =
        aibsvcMinWorkerAttackersHarvesting;
      enumMap["MinBuildSpacing"] = aibsvcMinBuildSpacing;
    }

    class FactionType
    {
    public:
      typedef pair < const UnitType *, int >PairPUnitTypeInt;
      typedef vector < UnitType > UnitTypes;
      typedef vector < UpgradeType > UpgradeTypes;
      typedef vector < PairPUnitTypeInt > StartingUnits;
      typedef vector < Resource > Resources;

    private:
      string name;
      UnitTypes unitTypes;
      UpgradeTypes upgradeTypes;
      StartingUnits startingUnits;
      Resources startingResources;
      StrSound *music;
      FactionPersonalityType personalityType;

      std::map < AIBehaviorUnitCategory,
        std::vector < PairPUnitTypeInt > >mapAIBehaviorUnitCategories;
      std::vector < const UpgradeType *>vctAIBehaviorUpgrades;
      std::map < AIBehaviorStaticValueCategory,
        int >mapAIBehaviorStaticOverrideValues;

      bool isLinked;

      float healthbarheight;
      float healthbarthickness;
      int healthbarVisible;
      bool healthbarBorderTextureEnabled;
      bool healthbarBackgroundTextureEnabled;
      bool healthbarLineBorder;
      Texture2D *healthbarTexture;
      Texture2D *healthbarBackgroundTexture;
      bool flatParticlePositions;

    public:
      //init
      FactionType ();
      void load (const string & factionName, const TechTree * techTree,
                 Checksum * checksum, Checksum * techtreeChecksum,
                 std::map < string, vector < pair < string,
                 string > > >&loadedFileList, bool validationMode = false);
      virtual ~ FactionType ();

      const std::vector < FactionType::PairPUnitTypeInt >
        getAIBehaviorUnits (AIBehaviorUnitCategory category) const;
      const std::vector < const UpgradeType *>getAIBehaviorUpgrades () const
      {
        return vctAIBehaviorUpgrades;
      };
      int getAIBehaviorStaticOverideValue (AIBehaviorStaticValueCategory type)
        const;

      //get
      bool getIsLinked () const
      {
        return isLinked;
      }
      int getUnitTypeCount () const
      {
        return (int) unitTypes.size ();
      }
      int getUpgradeTypeCount () const
      {
        return (int) upgradeTypes.size ();
      }
      virtual string getName (bool translatedValue = false) const;
      const UnitType *getUnitType (int i) const
      {
        return &unitTypes[i];
      }
      const UpgradeType *getUpgradeType (int i) const
      {
        return &upgradeTypes[i];
      }
      StrSound *getMusic () const
      {
        return music;
      }
      int getStartingUnitCount () const
      {
        return (int) startingUnits.size ();
      }
      const UnitType *getStartingUnit (int i) const
      {
        return startingUnits[i].first;
      }
      int getStartingUnitAmount (int i) const
      {
        return startingUnits[i].second;
      }
      inline float getHealthbarHeight () const
      {
        return healthbarheight;
      }
      inline float getHealthbarThickness () const
      {
        return healthbarthickness;
      }
      inline int getHealthbarVisible () const
      {
        return healthbarVisible;
      }
      inline bool isHealthbarBorderTextureEnabled () const
      {
        return healthbarBorderTextureEnabled;
      }
      inline bool isHealthbarBackgroundTextureEnabled () const
      {
        return healthbarBackgroundTextureEnabled;
      }
      inline bool isHealthbarLineBorder () const
      {
        return healthbarLineBorder;
      }
      Texture2D *getHealthbarTexture () const
      {
        return healthbarTexture;
      }
      Texture2D *getHealthbarBackgroundTexture () const
      {
        return healthbarBackgroundTexture;
      }
      bool isFlatParticlePositions () const
      {
        return flatParticlePositions;
      }


      const UnitType *getUnitType (const string & name) const;
      //const UnitType *getUnitTypeById(int id) const;
      const UpgradeType *getUpgradeType (const string & name) const;
      int getStartingResourceAmount (const ResourceType * resourceType) const;

      FactionPersonalityType getPersonalityType () const
      {
        return personalityType;
      }
      void setPersonalityType (FactionPersonalityType value)
      {
        personalityType = value;
      }

      std::string toString () const;
      std::vector < std::string > validateFactionType ();
      std::vector < std::string > validateFactionTypeResourceTypes (vector <
                                                                    ResourceType
                                                                    >
                                                                    &resourceTypes);
      std::vector < std::string > validateFactionTypeUpgradeTypes ();

      void deletePixels ();
      bool factionUsesResourceType (const ResourceType * rt) const;

    };

}}                              //end namespace

#endif
