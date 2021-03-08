#include "software/ai/passing/eighteen_zone_pitch_division.h"

#include "software/geom/point.h"
#include "software/geom/rectangle.h"

EighteenZonePitchDivision::EighteenZonePitchDivision(const Field& field)
{
    const double zone_width  = field.xLength() / 6;
    const double zone_height = field.yLength() / 3;

    for (double pos_x = -field.xLength() / 2; pos_x < field.xLength() / 2;
         pos_x += zone_width)
    {
        for (double pos_y = field.yLength() / 2; pos_y > -field.yLength() / 2;
             pos_y -= zone_height)
        {
            pitch_division.emplace_back(Rectangle(
                Point(pos_x, pos_y), Point(pos_x + zone_width, pos_y - zone_height)));
        }
    }
}

const Rectangle& EighteenZonePitchDivision::getZone(EighteenZoneId zone_id) const
{
    return pitch_division[static_cast<unsigned>(zone_id)];
}

inline size_t EighteenZonePitchDivision::getTotalNumberOfZones() const
{
    return sizeEighteenZoneId();
}
