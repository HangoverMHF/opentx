/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _FLIGHTMODES_H_
#define _FLIGHTMODES_H_

#include "modeledit.h"
#include "eeprominterface.h"

class RawSwitchFilterItemModel;

constexpr char MIMETYPE_FLIGHTMODE[] = "application/x-companion-flightmode";
constexpr char MIMETYPE_GVAR_PARAMS[]  = "application/x-companion-gvar-params";
constexpr char MIMETYPE_GVAR_VALUE[] = "application/x-companion-gvar-value";

namespace Ui {
  class FlightMode;
}

class FlightModePanel : public ModelPanel
{
    Q_OBJECT

  public:
    FlightModePanel(QWidget *parent, ModelData &model, int modeIdx, GeneralSettings & generalSettings, Firmware * firmware, RawSwitchFilterItemModel * switchModel);
    virtual ~FlightModePanel();

    virtual void update();

  signals:
    void nameModified();
    void datachanged();

  private slots:
    void phaseName_editingFinished();
    void phaseSwitchChanged(int index);
    void phaseFadeIn_editingFinished();
    void phaseFadeOut_editingFinished();
    void phaseTrimUse_currentIndexChanged(int index);
    void phaseTrim_valueChanged();
    void phaseTrimSlider_valueChanged();
    void GVName_editingFinished();
    void phaseGVValue_editingFinished();
    void phaseGVUse_currentIndexChanged(int index);
    void phaseGVPopupToggled(bool checked);
    void phaseGVUnit_currentIndexChanged(int index);
    void phaseGVPrec_currentIndexChanged(int index);
    void phaseGVMin_editingFinished();
    void phaseGVMax_editingFinished();
    void phaseREValue_editingFinished();
    void phaseREUse_currentIndexChanged(int index);
    void onCustomContextMenuRequested(QPoint pos);
    void cmClear();
    void cmClearAll();
    void cmCopy();
    void cmCut();
    void cmDelete();
    void cmInsert();
    void cmPaste();
    void cmMoveDown();
    void cmMoveUp();
    void gvOnCustomContextMenuRequested(QPoint pos);
    void gvCmClear();
    void gvCmClearAll();
    void gvCmCopy();
    void gvCmCut();
    void gvCmDelete();
    void gvCmInsert();
    void gvCmPaste();
    void gvCmMoveDown();
    void gvCmMoveUp();

  private:
    Ui::FlightMode *ui;
    int phaseIdx;
    FlightModeData & phase;
    int fmCount;
    int reCount;
    int gvCount;
    int gvIdx;
    int trimCount;
    QVector<QLabel *> trimsLabel;
    QLineEdit * gvNames[CPN_MAX_GVARS];
    QDoubleSpinBox * gvValues[CPN_MAX_GVARS];
    QCheckBox * gvPopups[CPN_MAX_GVARS];
    QComboBox * gvUse[CPN_MAX_GVARS];
    QComboBox * gvUnit[CPN_MAX_GVARS];
    QComboBox * gvPrec[CPN_MAX_GVARS];
    QDoubleSpinBox * gvMin[CPN_MAX_GVARS];
    QDoubleSpinBox * gvMax[CPN_MAX_GVARS];
    QSpinBox * reValues[CPN_MAX_ENCODERS];
    QComboBox * reUse[CPN_MAX_ENCODERS];
    QVector<QComboBox *> trimsUse;
    QVector<QSpinBox *> trimsValue;
    QVector<QSlider *> trimsSlider;
    RawSwitchFilterItemModel * rawSwitchItemModel;
    Board::Type board;

    void trimUpdate(unsigned int trim);
    void updateGVar(int index);
    void updateRotaryEncoder(int index);
    void setGVSB(QDoubleSpinBox * spinBox, int min, int max, int val);
    void populateGvarUnitCB(QComboBox * cb);
    void populateGvarPrecCB(QComboBox * cb);
    bool hasClipboardData(QByteArray * data = nullptr) const;
    bool insertAllowed() const;
    bool moveDownAllowed() const;
    bool moveUpAllowed() const;
    void swapData(int idx1, int idx2);
    bool gvHasClipboardData() const;
    bool gvHasDefnClipboardData(QByteArray * data = nullptr) const;
    bool gvHasValueClipboardData(QByteArray * data = nullptr) const;
    bool gvDeleteAllowed() const;
    bool gvInsertAllowed() const;
    bool gvMoveDownAllowed() const;
    bool gvMoveUpAllowed() const;
    void gvSwapData(int idx1, int idx2);
};

class FlightModesPanel : public ModelPanel
{
    Q_OBJECT

  public:
    FlightModesPanel(QWidget *parent, ModelData & model, GeneralSettings & generalSettings, Firmware * firmware);
    virtual ~FlightModesPanel();

  public slots:
    virtual void update() override;

  signals:
    void updated();

  private slots:
    void onPhaseNameChanged();

  private:
    QString getTabName(int index);

    int modesCount;
    QTabWidget *tabWidget;

};

#endif // _FLIGHTMODES_H_

