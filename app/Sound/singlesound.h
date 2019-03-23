﻿#ifndef SINGLESOUND_H
#define SINGLESOUND_H
#include "Animators/complexanimator.h"
#include "Animators/qrealanimator.h"
class FixedLenAnimationRect;

class SingleSound : public ComplexAnimator {
    Q_OBJECT
public:
    SingleSound(const QString &path,
                FixedLenAnimationRect *durRect = nullptr);

    void setDurationRect(FixedLenAnimationRect *durRect);

    void setFilePath(const QString &path);
    void reloadDataFromFile();

    int getStartAbsFrame() const;
    int getSampleCount() const;
    const float *getFinalData() const;
    void prepareFinalData(const float &fps,
                          const int &minAbsFrame,
                          const int &maxAbsFrame);
    void drawTimelineControls(QPainter * const p,
                              const qreal &pixelsPerFrame,
                              const FrameRange &absFrameRange,
                              const int &rowHeight);
    DurationRectangleMovable *anim_getRectangleMovableAtPos(
            const int &relX, const int &minViewedFrame,
            const qreal &pixelsPerFrame);
    void updateFinalDataIfNeeded(const qreal &fps,
                                 const int &minAbsFrame,
                                 const int &maxAbsFrame);
    int prp_getFrameShift() const;

    bool SWT_shouldBeVisible(const SWT_RulesCollection &rules,
                             const bool &parentSatisfies,
                             const bool &parentMainTarget) const;
    FixedLenAnimationRect *getDurationRect();
public slots:
    void scheduleFinalDataUpdate();
private slots:
    void updateAfterDurationRectangleShifted();
private:
    bool mFinalDataUpdateNeeded = false;
    bool mOwnDurationRectangle;

    int mFinalAbsStartFrame = 0;
    int mSrcSampleCount = 0;
    int mFinalSampleCount = 0;

    QString mPath;

    float *mSrcData = nullptr;
    float *mFinalData = nullptr;

    FixedLenAnimationRect *mDurationRectangle = nullptr;

    qsptr<QrealAnimator> mVolumeAnimator =
            SPtrCreate(QrealAnimator)(100., 0., 200., 1., "volume");
};

#endif // SINGLESOUND_H
