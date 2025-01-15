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

#include "eevent.h"

eEvent::eEvent(const QVector3D pos, const QVector3D lastPos,
               const QVector3D lastPressPos, const bool mouseGrabbing,
               const qreal scale, const QVector3D& globalPos,
               const Qt::MouseButtons buttons,
               const Qt::KeyboardModifiers modifiers,
               const ulong& timestamp,
               std::function<void()> releaseMouse,
               std::function<void()> grabMouse,
               QWidget* const widget) :
    fPos(pos), fLastPos(lastPos), fLastPressPos(lastPressPos),
    fMouseGrabbing(mouseGrabbing), fScale(scale),
    fGlobalPos(globalPos), fButtons(buttons),
    fModifiers(modifiers), fTimestamp(timestamp),
    fReleaseMouse(releaseMouse), fGrabMouse(grabMouse),
    fWidget(widget) {}

eMouseEvent::eMouseEvent(const bool synth,
                         const QVector3D pos, const QVector3D lastPos,
                         const QVector3D lastPressPos, const bool mouseGrabbing,
                         const qreal scale, const QVector3D& globalPos,
                         const Qt::MouseButton button,
                         const Qt::MouseButtons buttons,
                         const Qt::KeyboardModifiers modifiers,
                         const ulong& timestamp,
                         std::function<void()> releaseMouse,
                         std::function<void()> grabMouse,
                         QWidget* const widget) :
    eEvent(pos, lastPos, lastPressPos,
           mouseGrabbing,
           scale, globalPos,
           buttons, modifiers,
           timestamp,
           releaseMouse, grabMouse,
           widget), fSynth(synth), fButton(button) {}

eMouseEvent::eMouseEvent(const QVector3D pos, const QVector3D lastPos,
                         const QVector3D lastPressPos, const bool mouseGrabbing,
                         const qreal scale, const QMouseEvent* const e,
                         std::function<void()> releaseMouse,
                         std::function<void()> grabMouse,
                         QWidget* const widget) :
    eMouseEvent(e->source() != Qt::MouseEventNotSynthesized,
                pos, lastPos, lastPressPos, mouseGrabbing,
                scale, e->globalPos(), e->button(),
                e->buttons(), e->modifiers(), e->timestamp(),
                releaseMouse, grabMouse, widget) {}

eKeyEvent::eKeyEvent(const QVector3D pos, const QVector3D lastPos,
                     const QVector3D lastPressPos, const bool mouseGrabbing,
                     const qreal scale, const QVector3D globalPos,
                     const Qt::MouseButtons buttons, const QKeyEvent* const e,
                     std::function<void()> releaseMouse,
                     std::function<void()> grabMouse,
                     QWidget* const widget) :
    eMouseEvent(true, pos, lastPos, lastPressPos,
                mouseGrabbing, scale, globalPos,
                Qt::NoButton, buttons,
                e->modifiers(), e->timestamp(),
                releaseMouse, grabMouse, widget),
    fAutorepeat(e->isAutoRepeat()),
    fType(e->type()), fKey(e->key()) {}
