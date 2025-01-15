/*
#
# Friction - https://friction.graphics
#
# Copyright (c) Ole-André Rodlie and contributors
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# See 'README.md' for more information.
#
*/

// Fork of enve - Copyright (C) 2016-2020 Maurycy Liebner

#ifndef QVector3DAnimator_H
#define QVector3DAnimator_H
#include "staticcomplexanimator.h"
#include "../skia/skiaincludes.h"

class CORE_EXPORT QVector3DAnimator : public StaticComplexAnimator {
    e_OBJECT
protected:
    QVector3DAnimator(const QString& name);
    QVector3DAnimator(const QPointF& iniValue,
                    const QPointF& minValue,
                    const QPointF& maxValue,
                    const QPointF& valueStep,
                    const QString& name);
    QVector3DAnimator(const QPointF& iniValue,
                    const QPointF& minValue,
                    const QPointF& maxValue,
                    const QPointF& valueStep,
                    const QString& nameX,
                    const QString& nameY,
                    const QString& name);
public:
    QJSValue prp_getBaseJSValue(QJSEngine& e) const;
    QJSValue prp_getBaseJSValue(QJSEngine& e, const qreal relFrame) const;
    QJSValue prp_getEffectiveJSValue(QJSEngine& e) const;
    QJSValue prp_getEffectiveJSValue(QJSEngine& e, const qreal relFrame) const;

    void setBaseValue(const qreal valX, const qreal valY, const qreal valZ) {
        setBaseValue({valX, valY, valZ});
    }
    void setBaseValue(const QVector3D &val);

    void setBaseValueWithoutCallingUpdater(const QVector3D &val);
    void incBaseValuesWithoutCallingUpdater(const qreal x, const qreal y);
    void incBaseValues(const qreal x, const qreal y);
    void multCurrentValues(const qreal sx, const qreal sy);

    QVector3D getSavedValue();
    qreal getSavedXValue();
    qreal getSavedYValue();

    void incAllBaseValues(const qreal x, const qreal y);

    QrealAnimator *getXAnimator();
    QrealAnimator *getYAnimator();

    void multSavedValueToCurrentValue(const qreal sx,
                                      const qreal sy);
    void incSavedValueToCurrentValue(const qreal incXBy,
                                     const qreal incYBy);

    void setValuesRange(const qreal minVal, const qreal maxVal);

    QVector3D getBaseValue() const;
    QVector3D getBaseValueAtAbsFrame(const qreal frame) const;
    QVector3D getBaseValue(const qreal relFrame) const;

    void setPrefferedValueStep(const qreal valueStep);

    bool getBeingTransformed();

    QVector3D getEffectiveValue() const;
    QVector3D getEffectiveValueAtAbsFrame(const qreal frame) const;
    QVector3D getEffectiveValue(const qreal relFrame) const;

    qreal getEffectiveXValue();
    qreal getEffectiveXValue(const qreal relFrame);

    qreal getEffectiveYValue();
    qreal getEffectiveYValue(const qreal relFrame);

    void applyTransform(const QMatrix4x4 &transform);

    void saveQPointFSVG(SvgExporter& exp,
                        QDomElement& parent,
                        const FrameRange& visRange,
                        const QString& name,
                        const bool transform = false,
                        const QString& type = "") const;
    void saveQPointFSVGX(SvgExporter& exp,
                         QDomElement& parent,
                         const FrameRange& visRange,
                         const QString& name,
                         const qreal y,
                         const qreal multiplier,
                         const bool transform = false,
                         const QString& type = "",
                         const QString& beginEvent = "",
                         const QString& endEvent = "",
                         const bool motion = false,
                         const bool motionRotate = false,
                         const QString & motionPath = QString()) const;
    void saveQPointFSVGY(SvgExporter& exp,
                         QDomElement& parent,
                         const FrameRange& visRange,
                         const QString& name,
                         const qreal x,
                         const qreal multiplier,
                         const bool transform = false,
                         const QString& type = "",
                         const QString& beginEvent = "",
                         const QString& endEvent = "",
                         const bool motion = false,
                         const bool motionRotate = false,
                         const QString & motionPath = QString()) const;
    QDomElement prp_writePropertyXEV_impl(const XevExporter& exp) const;
protected:
    qsptr<QrealAnimator> mXAnimator;
    qsptr<QrealAnimator> mYAnimator;
};

#endif // QVector3DAnimator_H
