#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "software/ai/passing/cost_function.h"
#include "software/geom/point.h"
#include "software/geom/vector.h"
#include "software/geom/angle.h"
#include "software/world/field.h"
#include "software/world/robot.h"

namespace py = pybind11;


PYBIND11_MODULE(cost_function_python_wrapper, m) {

    // Geometry Classes
    py::class_<Point>(m, "Point")
        .def(py::init<double, double>())
        .def("x", &Point::x)
        .def("y", &Point::y)
        .def("setX", &Point::setX)
        .def("setY", &Point::setY);

    py::class_<Vector>(m, "Vector")
        .def(py::init<double, double>())
        .def("x", &Vector::x)
        .def("y", &Vector::y)
        .def("setX", &Vector::setX)
        .def("setY", &Vector::setY);

    py::class_<Angle>(m, "Angle")
        .def(py::init([](double rad) {
            return Angle::fromRadians(rad);
        }));

    // Timestamp Class
    py::class_<Timestamp>(m, "Timestamp")
        .def(py::init([](double seconds) {
            return Timestamp::fromSeconds(seconds);
        }))
        .def(py::init([](double milliseconds) {
            return Timestamp::fromMilliseconds(milliseconds);
        }));

    // World Classes
    py::class_<Field>(m, "Field")
        .def(py::init<double, double, double, double,
                      double, double, double, double>());

    py::class_<Robot>(m, "Robot")
        .def(py::init<unsigned, Point&, Vector&, Angle&, Angle&, Timestamp&>())
        .def("timestamp", &Robot::timestamp)
        .def("position", &Robot::position)
        .def("velocity", &Robot::velocity)
        .def("orientation", &Robot::orientation)
        .def("angularVelocity", &Robot::angularVelocity);

    py::class_<Team>(m, "Team")
        .def(py::init<const std::vector<Robot>&>())
        .def("assignGoalie", &Team::assignGoalie);

    // Pass Generator Classes
    py::class_<Pass>(m, "Pass")
        .def(py::init<Point, Point, double, Timestamp>())
        .def("receiverPoint", &Pass::receiverPoint)
        .def("receiverOrientation", &Pass::receiverOrientation)
        .def("passerOrientation", &Pass::passerOrientation)
        .def("passerPoint", &Pass::passerPoint)
        .def("speed", &Pass::speed)
        .def("startTime", &Pass::startTime)
        .def("estimateReceiveTime", &Pass::estimateReceiveTime)
        .def("estimatePassDuration", &Pass::estimatePassDuration);

    // Cost Functions
    m.def("ratePass", &ratePass);
    m.def("ratePassShootScore", &ratePassShootScore);
    m.def("ratePassShootScoreApproximately", &ratePassShootScoreApproximately);
    m.def("ratePassEnemyRisk", &ratePassEnemyRisk);
    m.def("ratePassFriendlyCapability", &ratePassFriendlyCapability);
    m.def("getStaticPositionQuality", &getStaticPositionQuality);

    // Overloaded Cost Functions
    m.def("calculateInterceptRiskTeam", py::overload_cast<const Team&, const Pass&>(&calculateInterceptRisk));
    m.def("calculateInterceptRiskRobot", py::overload_cast<const Robot&, const Pass&>(&calculateInterceptRisk));
}
