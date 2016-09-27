#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <SNAPComponent.h>
#include <SNAPCommon.h>

class RegistrationModel;
class QAbstractButton;
class OptimizationProgressRenderer;

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public SNAPComponent
{
  Q_OBJECT

public:
  explicit RegistrationDialog(QWidget *parent = 0);
  ~RegistrationDialog();

  void SetModel(RegistrationModel *model);

signals:

  void wizardFinished();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_btnRunRegistration_clicked();

  void on_btnLoad_clicked();

  void on_btnSave_clicked();

  void on_buttonBox_clicked(QAbstractButton *button);

  void on_tabWidget_currentChanged(int index);

private:
  Ui::RegistrationDialog *ui;

  RegistrationModel *m_Model;

  int GetTransformFormat(QString &format);

  // This is a bit unfortunate but we need to keep a list of renderers for the
  // plot widgets currently shown
  typedef SmartPtr<OptimizationProgressRenderer> RendererPtr;

  std::vector<RendererPtr> m_PlotRenderers;


};

#endif // REGISTRATIONDIALOG_H
