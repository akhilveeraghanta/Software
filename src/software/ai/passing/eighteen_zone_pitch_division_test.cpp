#include "software/ai/passing/eighteen_zone_pitch_division.h"

#include <gtest/gtest.h>

#include "software/geom/algorithms/contains.h"
#include "software/world/field.h"


TEST(EighteenZonePitchDivision, test_pitch_division_div_a)
{
    auto field          = Field::createSSLDivisionAField();
    auto pitch_division = EighteenZonePitchDivision(field);

    // from the pitch division diagram in eighteen_zone_pitch_division.h
    // we know that zones 1 - 9 should be on the friendly side and
    // zones 10 - 18 should be on the enemy side.
    for (EighteenZoneId zone : {
             EighteenZoneId::ZONE_1,
             EighteenZoneId::ZONE_2,
             EighteenZoneId::ZONE_3,
             EighteenZoneId::ZONE_4,
             EighteenZoneId::ZONE_5,
             EighteenZoneId::ZONE_6,
             EighteenZoneId::ZONE_7,
             EighteenZoneId::ZONE_8,
             EighteenZoneId::ZONE_9,
         })
    {
        ASSERT_TRUE(
            contains(field.friendlyHalf(), pitch_division.getZone(zone).centre()));
    }

    for (EighteenZoneId zone : {
             EighteenZoneId::ZONE_10,
             EighteenZoneId::ZONE_11,
             EighteenZoneId::ZONE_12,
             EighteenZoneId::ZONE_13,
             EighteenZoneId::ZONE_14,
             EighteenZoneId::ZONE_15,
             EighteenZoneId::ZONE_16,
             EighteenZoneId::ZONE_17,
             EighteenZoneId::ZONE_18,
         })
    {
        ASSERT_TRUE(contains(field.enemyHalf(), pitch_division.getZone(zone).centre()));
    }
}

TEST(EighteenZonePitchDivision, test_pitch_division_div_b)
{
    auto field          = Field::createSSLDivisionBField();
    auto pitch_division = EighteenZonePitchDivision(field);

    // from the pitch division diagram in eighteen_zone_pitch_division.h
    // we know that zones 1 - 9 should be on the friendly side and
    // zones 10 - 18 should be on the enemy side.
    for (EighteenZoneId zone : {
             EighteenZoneId::ZONE_1,
             EighteenZoneId::ZONE_2,
             EighteenZoneId::ZONE_3,
             EighteenZoneId::ZONE_4,
             EighteenZoneId::ZONE_5,
             EighteenZoneId::ZONE_6,
             EighteenZoneId::ZONE_7,
             EighteenZoneId::ZONE_8,
             EighteenZoneId::ZONE_9,
         })
    {
        ASSERT_TRUE(
            contains(field.friendlyHalf(), pitch_division.getZone(zone).centre()));
    }

    for (EighteenZoneId zone : {
             EighteenZoneId::ZONE_10,
             EighteenZoneId::ZONE_11,
             EighteenZoneId::ZONE_12,
             EighteenZoneId::ZONE_13,
             EighteenZoneId::ZONE_14,
             EighteenZoneId::ZONE_15,
             EighteenZoneId::ZONE_16,
             EighteenZoneId::ZONE_17,
             EighteenZoneId::ZONE_18,
         })
    {
        ASSERT_TRUE(contains(field.enemyHalf(), pitch_division.getZone(zone).centre()));
    }
}

TEST(EighteenZonePitchDivision, test_iteration)
{
    auto field          = Field::createSSLDivisionBField();
    auto pitch_division = EighteenZonePitchDivision(field);

    for (EighteenZoneId zone_id : pitch_division.getAllZoneIds())
    {
        ASSERT_TRUE(
            contains(field.fieldLines(), pitch_division.getZone(zone_id).centre()));
    }
}
