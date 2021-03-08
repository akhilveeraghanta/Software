#include "software/ai/passing/pass_evaluation.h"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "software/ai/passing/field_pitch_division.h"
#include "software/ai/passing/pass.h"
#include "software/ai/passing/pass_with_rating.h"
#include "software/geom/point.h"
#include "software/time/timestamp.h"

template <class ZoneEnum>
PassEvaluation<ZoneEnum>::PassEvaluation(
    std::shared_ptr<const FieldPitchDivision<ZoneEnum>> pitch_division,
    std::unordered_map<ZoneEnum, PassWithRating> best_pass_in_zones, Timestamp timestamp)
    : pitch_division_(pitch_division),
      best_pass_in_zones_(best_pass_in_zones),
      timestamp_(timestamp)
{
}

template <class ZoneEnum>
PassWithRating PassEvaluation<ZoneEnum>::getBestPassOnField() const
{
    auto best_pass =
        std::max_element(best_pass_in_zones_.begin(), best_pass_in_zones_.end(),
                         [](const std::pair<ZoneEnum, PassWithRating> &p1,
                            const std::pair<ZoneEnum, PassWithRating> &p2) {
                             return p1.second.rating < p1.second.rating;
                         });
    return (*best_pass).second;
}

template <class ZoneEnum>
PassWithRating PassEvaluation<ZoneEnum>::getBestPassInZones(
    const std::unordered_set<ZoneEnum> &zone_ids) const
{
    if (zone_ids.size() == 0)
    {
        throw std::invalid_argument("no zone_ids provided");
    }

    auto compare_pass_rating = [this](ZoneEnum zone_a, ZoneEnum zone_b) {
        return best_pass_in_zones_.at(zone_a).rating < best_pass_in_zones_.at(zone_b).rating;
    };

    ZoneEnum best_zone =
        *std::max_element(zone_ids.begin(), zone_ids.end(), compare_pass_rating);

    return best_pass_in_zones_.at(best_zone);
}

template <class ZoneEnum>
std::shared_ptr<const FieldPitchDivision<ZoneEnum>>
PassEvaluation<ZoneEnum>::getFieldPitchDivsion() const
{
    return pitch_division_;
}

template <class ZoneEnum>
Timestamp PassEvaluation<ZoneEnum>::getEvaluationTime() const
{
    return timestamp_;
}
