/*=========================================================================

  Program:   ITK-SNAP
  Module:    $RCSfile: Filename.cxx,v $
  Language:  C++
  Date:      $Date: 2010/10/18 11:25:44 $
  Version:   $Revision: 1.12 $
  Copyright (c) 2011 Paul A. Yushkevich

  This file is part of ITK-SNAP

  ITK-SNAP is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

=========================================================================*/

#ifndef GENERICSLICEVIEW_H
#define GENERICSLICEVIEW_H

#include <QGLWidget>
#include <SNAPCommon.h>
#include <GenericSliceModel.h>
#include <GenericSliceRenderer.h>
#include <SNAPQGLWidget.h>

class CrosshairsInteractionMode;

class GenericSliceView : public SNAPQGLWidget
{
  Q_OBJECT

public:
  explicit GenericSliceView(QWidget *parent = 0);

  irisGetMacro(Model, GenericSliceModel *)

  GenericSliceRenderer &GetRenderer() { return m_Renderer; }
  const GenericSliceRenderer &GetRenderer() const { return m_Renderer; }

  // Set the model (state) for this widget
  void SetModel(GenericSliceModel *model);

  // Callback for geometry update events
  void OnModelUpdate();

public slots:

protected:

  // OpenGL painter methods
  void paintGL();
  void resizeGL(int w, int h);
  void initializeGL();

  void enterEvent(QEvent *);
  void leaveEvent(QEvent *);

  void resizeEvent(QResizeEvent *);

  // Pointer to the model object for this class
  GenericSliceModel *m_Model;

  // OpenGL renderer (owned by the view)
  GenericSliceRenderer m_Renderer;

  // Whether next repaint requires a resize call (Qt bug?)
  bool m_NeedResizeOnNextRepaint;

  CrosshairsInteractionMode *m_Crosshairs;
};

#endif // GENERICSLICEVIEW_H