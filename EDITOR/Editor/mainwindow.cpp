#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imagedisplayer.h"
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fpath(""),
    newwin(nullptr)
{
    ui->setupUi(this);
    // Line Eedits
    weapName = ui->lineWeaponName;
    weapDesc = ui->lineWeaponDescription;
    projType = ui->lineProjectileType;
    weapPrincipe = ui->lineWeaponPrincipe;
    // Spin Boxes
    dmgMin = ui->spinDmgMin;
    dmgMax = ui->spinDmgMax;
    critDmgMin = ui->spinCritDmgMin;
    critDmgMax = ui->spinCritDmgMax;

    projAmount = ui->spinProjectileAmount;
    clipSize = ui->spinClipSize;
    ammoPerShoot = ui->spinAmmoPerShoot;
    maxScatter = ui->spinMaxScatter;
    // Double Spin Boxes
    shootCooldown = ui->dspShootCooldown;
    reloadTime = ui->dspReloadTime;
    nextDmgCooldown = ui->dspDmgCooldown;

    // Radio Buttons
    canCrit = ui->radioCrits;
    // Push Buttons
    pngload = ui->pushButtonPNGLoad;
    pngShootload = ui->pushButtonPNGShootLoad;
    pngProjload = ui->pushButtonPNGProjectileLoad;

    // Default pngs
    png = pngShoot = pngProj = pngAdd = pngAdd2 = "";

    // Add imagedisplayers to all zones
    idPNG = new ImageDisplayer(this);
    ui->zonePNG->addWidget(idPNG);

    idPNGShoot = new ImageDisplayer(this);
    ui->zonePNGShoot->addWidget(idPNGShoot);

    idPNGProj = new ImageDisplayer(this);
    ui->zonePNGProj->addWidget(idPNGProj);

    idPNGAdd = new ImageDisplayer(this);
    ui->zonePNGAdd->addWidget(idPNGAdd);

    idPNGAdd2 = new ImageDisplayer(this);
    ui->zonePNGAdd2->addWidget(idPNGAdd2);
}

MainWindow::~MainWindow()
{
    delete idPNG, idPNGShoot, idPNGProj, idPNGAdd, idPNGAdd2;
    delete ui;
}

void MainWindow::PNGclick(QString& change, ImageDisplayer* displayer)
{
    change = QFileDialog::getOpenFileName(
                this, tr("Изображение"),
                ((displayer->getPNGPath() == "") ?
                    QDir::currentPath() :
                    (displayer->getPNGPath())),
                "All Files (*.*) ;; PNG Files (*.png)");
    if (!change.isNull())
    {
        displayer->setPNG(change);
    }
    else
    {
        change = "";
        displayer->resetAll();
    }
}

void MainWindow::on_pushButtonPNGLoad_clicked()
{
    PNGclick(png, idPNG);
}

void MainWindow::on_pushButtonPNGShootLoad_clicked()
{
    PNGclick(pngShoot, idPNGShoot);
}

void MainWindow::on_pushButtonPNGProjectileLoad_clicked()
{
    PNGclick(pngProj, idPNGProj);
}

void MainWindow::on_pushButtonPNGAdditionalLoad_clicked()
{
    PNGclick(pngAdd, idPNGAdd);
}

void MainWindow::on_pushButtonPNGAdditionalLoad_2_clicked()
{
    PNGclick(pngAdd2, idPNGAdd2);
}

// MAIN FUNCTIONS
// SAVE
void MainWindow::on_weapSave_triggered()
{
    qDebug() << "currload: " << fpath;
    qDebug() << ((!QFileInfo(fpath).exists()) ? "noex" : "ex");
    if (fpath == "" || !QFileInfo(fpath).exists()) // no file yet
    {
        // save current params to a file
        fpath = QFileDialog::getSaveFileName(
                this,
                "Сохранить оружие",
                QDir::currentPath(),
                "Weapon Design Files (*.wpd)");
    }

    if (!fpath.isNull())
    {
        // have something to work with
        QFile file(fpath);
        file.open(QIODevice::WriteOnly);

        QXmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("weapon");
        writer.writeTextElement("name", weapName->text());
        writer.writeTextElement("desc", weapDesc->text());
        writer.writeTextElement("projectiletype", projType->text());
        writer.writeTextElement("principe", weapPrincipe->toPlainText());

        writer.writeTextElement("dmgmin", QString::number(dmgMin->value()));
        writer.writeTextElement("dmgmax", QString::number(dmgMax->value()));
        writer.writeTextElement("critdmgmin", QString::number(critDmgMin->value()));
        writer.writeTextElement("critdmgmax", QString::number(critDmgMax->value()));
        writer.writeTextElement("projamount", QString::number(projAmount->value()));
        writer.writeTextElement("shootcooldown", QString::number(shootCooldown->value()));
        writer.writeTextElement("reloadtime", QString::number(reloadTime->value()));
        writer.writeTextElement("clipsize", QString::number(clipSize->value()));
        writer.writeTextElement("ammopershot", QString::number(ammoPerShoot->value()));
        writer.writeTextElement("nextdmgcooldown", QString::number(nextDmgCooldown->value()));
        writer.writeTextElement("maxscatter", QString::number(maxScatter->value()));

        writer.writeTextElement("cancrit", (canCrit->isChecked()) ? "1" : "0");

        writer.writeTextElement("pathpng", png);
        writer.writeTextElement("pathpngShoot", pngShoot);
        writer.writeTextElement("pathpngProjectile", pngProj);
        writer.writeTextElement("pathpngAdd", pngAdd);
        writer.writeTextElement("pathpngAdd2", pngAdd2);

        writer.writeEndElement();

        writer.writeEndDocument();

        file.close();
    }
}

// LOAD
void MainWindow::on_weapLoad_triggered()
{
    QString loadpath = QFileDialog::getOpenFileName(
                    this,
                    "Загрузить оружие",
                    QDir::currentPath(),
                    "Weapon Design Files (*.wpd)");
    if (!loadpath.isNull())
    {
        qDebug() << "currloadpath: " << loadpath;
        // have something to work with
        fpath = loadpath;
        QFile file(fpath);
        file.open(QIODevice::ReadOnly | QFile::Text);

        QXmlStreamReader reader;
        reader.setDevice(&file);
        //reader.readNext();

        while (!reader.atEnd())
        {
            if (reader.isStartElement())
            {
                auto n = reader.name();
                // TEXT BOXES/LINES
                if (n == "name")
                {
                    weapName->setText(reader.readElementText());
                    reader.readNext();
                }
                else if (n == "desc")
                {
                    weapDesc->setText(reader.readElementText());
                    reader.readNext();
                }
                else if (n == "projectiletype")
                {
                    projType->setText(reader.readElementText());
                    reader.readNext();
                }
                else if (n == "principe")
                {
                    weapPrincipe->setText(reader.readElementText());
                    reader.readNext();
                }
                // SPINS
                else if (n == "dmgmin")
                {
                    dmgMin->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }
                else if (n == "dmgmax")
                {
                    dmgMax->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }
                else if (n == "critdmgmin")
                {
                    critDmgMin->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }
                else if (n == "critdmgmax")
                {
                    critDmgMax->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }
                else if (n == "projamount")
                {
                    projAmount->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }
                else if (n == "shootcooldown")
                {
                    shootCooldown->setValue(reader.readElementText().toDouble());
                    reader.readNext();
                }
                else if (n == "reloadtime")
                {
                    reloadTime->setValue(reader.readElementText().toDouble());
                    reader.readNext();
                }
                else if (n == "nextdmgcooldown")
                {
                    nextDmgCooldown->setValue(reader.readElementText().toDouble());
                    reader.readNext();
                }                else if (n == "clipsize")
                {
                    clipSize->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }
                else if (n == "ammopershot")
                {
                    ammoPerShoot->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }

                else if (n == "maxscatter")
                {
                    maxScatter->setValue(reader.readElementText().toInt());
                    reader.readNext();
                }
                // BOOLEAN RADIO BUTTONS
                else if (n == "cancrit")
                {
                    canCrit->setChecked(false);
                    if (reader.readElementText() == "1")
                        canCrit->setChecked(true);
                    reader.readNext();
                }
                // PATH STRINGS
                else if (n == "pathpng")
                {
                    png = reader.readElementText();
                    idPNG->setPNG(png);
                    reader.readNext();
                }
                else if (n == "pathpngShoot")
                {
                    pngShoot = reader.readElementText();
                    idPNGShoot->setPNG(pngShoot);
                    reader.readNext();
                }
                else if (n == "pathpngProjectile")
                {
                    pngProj = reader.readElementText();
                    idPNGProj->setPNG(pngProj);
                    reader.readNext();
                }
                else if (n == "pathpngAdd")
                {
                    pngAdd = reader.readElementText();
                    idPNGAdd->setPNG(pngAdd);
                    reader.readNext();
                }
                else if (n == "pathpngAdd2")
                {
                    pngAdd2 = reader.readElementText();
                    idPNGAdd2->setPNG(pngAdd2);
                    reader.readNext();
                }
                else
                    reader.readNext();
            }
            else
                reader.readNext();
        }

        file.close();
    }
}
// EXPORT
void MainWindow::on_weapExport_triggered()
{
    int imgw = 800,
        imgh = 480;
    QImage image(imgw, imgh, QImage::Format::Format_ARGB32_Premultiplied);
    image.fill(qRgba(0, 0, 0, 0));
    QString imagepath = QFileDialog::getSaveFileName(
                this,
                "Сохранить изображение",
                (fpath == "") ? QDir::currentPath() : fpath,
                "PNG files (*.png)");

    QPainter painter;
    painter.begin(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw pngs
    int nextyoff = 0;
    if (png != "")
    {
        QImage& imgmain = idPNG->getPNGImage().toImage();
        painter.drawImage(5, 5, imgmain);
        nextyoff = imgmain.height() + 5;
    }
    if (pngShoot != "")
    {
        QImage& imgshoot = idPNGShoot->getPNGImage().toImage();
        painter.drawImage(5, 5 + nextyoff, imgshoot);
        nextyoff += imgshoot.height() + 5;
    }
    if (pngProj != "")
    {
        QImage& imgproj = idPNGProj->getPNGImage().toImage();
        painter.drawImage(5, 5 + nextyoff, imgproj);
        nextyoff += imgproj.height() + 5;
    }
    if (pngAdd != "")
    {
        QImage& imgadd = idPNGAdd->getPNGImage().toImage();
        painter.drawImage(5, 5 + nextyoff, imgadd);
        nextyoff += imgadd.height() + 5;
    }
    if (pngAdd2 != "")
    {
        QImage& imgadd2 = idPNGAdd2->getPNGImage().toImage();
        painter.drawImage(5, 5 + nextyoff, imgadd2);
        nextyoff += imgadd2.height() + 5;
    }
    // write params
    QPen pen(qRgb(0, 0, 0));
    painter.setPen(pen);
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(14);

    painter.setFont(font);
    int xoff = 350,
        yoff = 30,
        yadd = yoff;
    painter.drawText(xoff, yoff, weapName->text());

    yoff += yadd;
    painter.drawText(xoff, yoff, weapDesc->text());

    int fsz = font.pointSize();
    font.setPointSize(14);
    painter.setFont(font);
    yoff += yadd;
    QRect principeRect(xoff, yoff, imgw-xoff, imgh-yoff);
    painter.drawText(principeRect, Qt::TextWordWrap, weapPrincipe->toPlainText());

    font.setPointSize(fsz);
    yoff += yadd + painter.boundingRect(principeRect, Qt::TextWordWrap, weapPrincipe->toPlainText()).height();
    painter.setFont(font);
    painter.drawText(xoff, yoff, "Параметры:");

    yoff += yadd;
    painter.drawText(QRect(150, yoff, 700, 1000), Qt::TextWordWrap,
        "Мин урон: " + QString::number(dmgMin->value()) + "   " //+ QString("\n")
        + "Макс урон: " + QString::number(dmgMax->value()) + QString("\n")
        + "Прож-лов: " + QString::number(projAmount->value()) + "   " //+ QString("\n")
        + "Выстрел кд: " + QString::number(shootCooldown->value()) + "\n"
        + "Перезарядка: " + QString::number(reloadTime->value()) + "   " // + "\n"
        + "Обойма: " + QString::number(clipSize->value()) + "\n"
        + "Патр за выстрел: " + QString::number(ammoPerShoot->value()) + "   " // + "\n"
        + "Кд на урон: " + QString::number(nextDmgCooldown->value()) + "\n"
        + "Разброс: " + QString::number(maxScatter->value()));
    if (canCrit->isChecked())
    {
        painter.drawText(QRect(500, yoff, 700, 1000), Qt::TextWordWrap,
            "Крит мин урон: " + QString::number(critDmgMin->value()) + "\n"
            + "Крит макс урон: " + QString::number(critDmgMax->value()));
    }

    painter.end();
    image.save(imagepath, "PNG");
}



void MainWindow::on_weapNew_triggered()
{
    if (newwin == nullptr)
    {
        newwin = new MainWindow();
        newwin->show();
        this->close();
    }
}
