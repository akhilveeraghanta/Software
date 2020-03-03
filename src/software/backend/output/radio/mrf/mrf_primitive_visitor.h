#pragma once

#include <array>
#include <optional>

#include "shared/proto/primitive.pb.h"
#include "software/ai/primitive/primitive_visitor.h"

/**
 * This class implements a Visitor that serializes the Primitive classes into packets
 * that can be send over the radio to the physical robots
 */
class MRFPrimitiveVisitor : public PrimitiveVisitor
{
   public:
    /**
     * Creates a new RadioSerializerPrimitiveVisitor
     */
    MRFPrimitiveVisitor() = default;

    /**
     * Serializes the given CatchPrimitive into a radio packet
     *
     * @param catch_primitive The CatchPrimitive to serialize
     */
    void visit(const CatchPrimitive &catch_primitive) override;

    /**
     * Serializes the given ChipPrimitive into a radio packet
     *
     * @param chip_primitive The ChipPrimitive to simulate */
    void visit(const ChipPrimitive &chip_primitive) override;

    /**
     * Serializes the given DirectVelocityPrimitive into a radio packet
     *
     * @param direct_velocity_primitive The DirectVelocityPrimitive to simulate
     */
    void visit(const DirectVelocityPrimitive &direct_velocity_primitive) override;

    /**
     * Visits a DirectWheelsPrimitive to perform an operation.
     *
     * @param direct_wheels_primitive The DirectWheelsPrimitive to visit
     */
    void visit(const DirectWheelsPrimitive &direct_wheels_primitive) override;

    /**
     * Visits a DribblePrimitive to perform an operation.
     *
     * @param dribble_primitive The DribblePrimitive to visit
     */
    void visit(const DribblePrimitive &dribble_primitive) override;

    /**
     * Serializes the given KickPrimitive into a radio packet
     *
     * @param kick_primitive The KickPrimitive to simulate
     */
    void visit(const KickPrimitive &kick_primitive) override;

    /**
     * Serializes the given MovePrimitive into a radio packet
     *
     * @param move_primitive The MovePrimitive to simulate
     */
    void visit(const MovePrimitive &move_primitive) override;

    /**
     * Serializes the given MoveSpinPrimitive into a radio packet
     *
     * @param movespin_primitive The MoveSpinPrimitive to simulate
     */
    void visit(const MoveSpinPrimitive &movespin_primitive) override;

    /**
     * Serializes the given PivotPrimitive into a radio packet
     *
     * @param pivot_primitive The PivotPrimitive to simulate
     */
    void visit(const PivotPrimitive &pivot_primitive) override;

    /**
     * Serializes the given StopPrimitive into a radio packet
     *
     * @param stop_primitive The StopPrimitive to simulate
     */
    void visit(const StopPrimitive &stop_primitive) override;

    /**
     * Returns the most recent serialized packet created by this
     * MRFPrimitiveVisitor (std::nullopt if no packet has been created).
     *
     * This is the radio packet created by one of the 'visit' functions.
     *
     * @return The most recent serialized packet created by this
     * MRFPrimitiveVisitor
     *
     * TODO update comment
     */
    std::string getSerializedRadioPacket();

   private:
    std::optional<RadioPrimitive> radio_prim;
};
