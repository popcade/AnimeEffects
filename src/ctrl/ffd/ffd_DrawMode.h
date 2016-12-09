#ifndef CTRL_FFD_DRAWMODE_H
#define CTRL_FFD_DRAWMODE_H

#include "core/Project.h"
#include "ctrl/ffd/ffd_Target.h"
#include "ctrl/ffd/ffd_IMode.h"
#include "ctrl/ffd/ffd_MoveVertices.h"

namespace ctrl {
namespace ffd {

class DrawMode : public IMode
{
public:
    DrawMode(core::Project& aProject, Targets& aTargets);
    virtual void updateParam(const FFDParam&);
    virtual bool updateCursor(const core::CameraInfo&, const core::AbstractCursor&);
    virtual void renderQt(const core::RenderInfo& aInfo, QPainter& aPainter);

private:
    enum State
    {
        State_Idle,
        State_Draw,
    };

    struct Status
    {
        Status();
        void clear();
        bool hasValidBrush() const;
        bool isDrawing() const { return state == State_Draw; }
        State state;
        util::Circle brush;
        MoveVertices* commandRef;
    };

    bool executeDrawTask(const QVector2D& aCenter, const QVector2D& aMove);

    core::Project& mProject;
    Targets& mTargets;
    FFDParam mParam;
    Status mStatus;
};

} // namespace ffd
} // namespace ctrl

#endif // CTRL_FFD_DRAWMODE_H
