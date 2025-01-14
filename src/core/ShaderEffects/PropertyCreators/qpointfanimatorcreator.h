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

#ifndef QPOINTFANIMATORCREATOR_H
#define QPOINTFANIMATORCREATOR_H

#include "Animators/qpointfanimator.h"
#include "shaderpropertycreator.h"

class CORE_EXPORT QPointFAnimatorCreator : public ShaderPropertyCreator {
    e_OBJECT
    QPointFAnimatorCreator(const QVector3D intF iniVal,
                           const QVector3D minVal,
                           const QVector3D maxVal,
                           const QVector3D step,
                           const bool glValue,
                           const QString& nameX,
                           const QString& nameY,
                           const QString& name,
                           const QString& nameUI) :
        ShaderPropertyCreator(glValue, name, nameUI),
        fIniVal(iniVal), fMinVal(minVal),
        fMaxVal(maxVal), fStep(step),
        fNameX(nameX), fNameY(nameY) {}

    const QVector3D fIniVal;
    const QVector3D fMinVal;
    const QVector3D fMaxVal;
    const QVector3D fStep;
    const QString fNameX;
    const QString fNameY;

    qsptr<Property> create() const {
        return enve::make_shared<QPointFAnimator>(
                    fIniVal, fMinVal, fMaxVal, fStep, fNameX, fNameY, fNameUI);
    }
};

#endif // QPOINTFANIMATORCREATOR_H
