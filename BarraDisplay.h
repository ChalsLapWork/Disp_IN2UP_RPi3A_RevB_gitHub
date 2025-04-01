/*
 * BarraDisplay.h
 *
 *  Created on: Jul 14, 2020
 *      Author: desarrollo-1
 */

#ifndef BARRADISPLAY_H_
#define BARRADISPLAY_H_






//---- Barra deteccion de Angulo Vibracion Menu------------------
#define POS_X1_BOX_AV        5   //INICIO X1 AJUSTE DE VIBRACION
#define POS_Y1_BOX_AV        35    //INICIO Y1   AJUSTE DE VIBRACION
#define POS_X2_BOX_AV        POS_X1_BOX_AV+LARGO_CUADRO_MADRE   //FIN X2 LARGO DE LA BOX PRINCIPAL X1-X2 AJUSTE DE VIBRACION
#define POS_Y2_BOX_AV        POS_Y1_BOX_AV+ALTURA_CUADRO_MADRE //FIN Y2 -> ALTURA BOX Y1-Y2   AJUSTE DE VIBRACION

#define POS_X1_BOX1_AV       POS_X1_BOX_AV+GAP_BOX   
#define POS_Y1_BOX1_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX1_AV       POS_X1_BOX_AV+ANCHO_BOX
#define POS_Y2_BOX1_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX2_AV       POS_X2_BOX1_AV+GAP_BOX   
#define POS_Y1_BOX2_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX2_AV       POS_X1_BOX2_AV+ANCHO_BOX
#define POS_Y2_BOX2_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX3_AV       POS_X2_BOX2_AV+GAP_BOX   
#define POS_Y1_BOX3_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX3_AV       POS_X1_BOX3_AV+ANCHO_BOX
#define POS_Y2_BOX3_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX4_AV       POS_X2_BOX3_AV+GAP_BOX   
#define POS_Y1_BOX4_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX4_AV       POS_X1_BOX4_AV+ANCHO_BOX
#define POS_Y2_BOX4_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX5_AV       POS_X2_BOX4_AV+GAP_BOX   
#define POS_Y1_BOX5_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX5_AV       POS_X1_BOX5_AV+ANCHO_BOX
#define POS_Y2_BOX5_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX6_AV       POS_X2_BOX5_AV+GAP_BOX   
#define POS_Y1_BOX6_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX6_AV       POS_X1_BOX6_AV+ANCHO_BOX
#define POS_Y2_BOX6_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX7_AV       POS_X2_BOX6_AV+GAP_BOX   
#define POS_Y1_BOX7_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX7_AV       POS_X1_BOX7_AV+ANCHO_BOX
#define POS_Y2_BOX7_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX8_AV       POS_X2_BOX7_AV+GAP_BOX   
#define POS_Y1_BOX8_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX8_AV       POS_X1_BOX8_AV+ANCHO_BOX
#define POS_Y2_BOX8_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX9_AV       POS_X2_BOX8_AV+GAP_BOX   
#define POS_Y1_BOX9_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX9_AV       POS_X1_BOX9_AV+ANCHO_BOX
#define POS_Y2_BOX9_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX10_AV       POS_X2_BOX9_AV+GAP_BOX   
#define POS_Y1_BOX10_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX10_AV       POS_X1_BOX10_AV+ANCHO_BOX
#define POS_Y2_BOX10_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX11_AV       POS_X2_BOX10_AV+GAP_BOX   
#define POS_Y1_BOX11_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX11_AV       POS_X1_BOX11_AV+ANCHO_BOX
#define POS_Y2_BOX11_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX12_AV       POS_X2_BOX11_AV+GAP_BOX   
#define POS_Y1_BOX12_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX12_AV       POS_X1_BOX12_AV+ANCHO_BOX
#define POS_Y2_BOX12_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX13_AV       POS_X2_BOX12_AV+GAP_BOX   
#define POS_Y1_BOX13_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX13_AV       POS_X1_BOX13_AV+ANCHO_BOX
#define POS_Y2_BOX13_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX14_AV       POS_X2_BOX13_AV+GAP_BOX   
#define POS_Y1_BOX14_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX14_AV       POS_X1_BOX14_AV+ANCHO_BOX
#define POS_Y2_BOX14_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX15_AV       POS_X2_BOX14_AV+GAP_BOX   
#define POS_Y1_BOX15_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX15_AV       POS_X1_BOX15_AV+ANCHO_BOX
#define POS_Y2_BOX15_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX16_AV       POS_X2_BOX15_AV+GAP_BOX   
#define POS_Y1_BOX16_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX16_AV       POS_X1_BOX16_AV+ANCHO_BOX
#define POS_Y2_BOX16_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX17_AV       POS_X2_BOX16_AV+GAP_BOX   
#define POS_Y1_BOX17_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX17_AV       POS_X1_BOX17_AV+ANCHO_BOX
#define POS_Y2_BOX17_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX18_AV       POS_X2_BOX17_AV+GAP_BOX   
#define POS_Y1_BOX18_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX18_AV       POS_X1_BOX18_AV+ANCHO_BOX
#define POS_Y2_BOX18_AV       POS_Y2_BOX_AV-GAP_BOX

#define POS_X1_BOX19_AV       POS_X2_BOX18_AV+GAP_BOX   
#define POS_Y1_BOX19_AV       POS_Y1_BOX_AV+GAP_BOX
#define POS_X2_BOX19_AV       POS_X1_BOX19_AV+ANCHO_BOX
#define POS_Y2_BOX19_AV       POS_Y2_BOX_AV-GAP_BOX
//fin de constantes de CUADRO DE DETECCION-----------------------------------------------------
// FIN DE CONSTANTES DE BARRA DE DETECCION +++++++++++++++++++++++++++++++++++++++++++++++++++++


//Konstantes REGENTES del GRAFICADOR de BARRA de DETECCION, GRAFICACION DE BARRA DE DETECCION CONSTANTES MAESTRAS
#define ALTURA_CUADRO_MADRE  18
#define LARGO_CUADRO_MADRE   228
#define GAP_BOX              2
#define ANCHO_BOX            10    //ANCHODE LA BOX

#define POS_X1_BOX1          POS_X1_BOX_PI+GAP_BOX   
#define POS_Y1_BOX1          POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX1          POS_X1_BOX_PI+ANCHO_BOX
#define POS_Y2_BOX1          POS_Y2_BOX_PI-GAP_BOX
      //PORTAL INICIO
#define POS_X1_BOX_PI        24    //INICIO X1 portal INICIO
#define POS_Y1_BOX_PI        48    //INICIO Y1   PORTAL INICIO
#define POS_X2_BOX_PI        POS_X1_BOX_PI+LARGO_CUADRO_MADRE   //FIN X2 LARGO DE LA BOX PRINCIPAL X1-X2 PORTAL INICIO
#define POS_Y2_BOX_PI        POS_Y1_BOX_PI+ALTURA_CUADRO_MADRE    //FIN Y2 -> ALTURA BOX Y1-Y2   PORTAL INICIO

#define POS_X1_BOX1_PI       POS_X1_BOX_PI+GAP_BOX   
#define POS_Y1_BOX1_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX1_PI       POS_X1_BOX_PI+ANCHO_BOX
#define POS_Y2_BOX1_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX2_PI       POS_X2_BOX1_PI+GAP_BOX   
#define POS_Y1_BOX2_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX2_PI       POS_X1_BOX2_PI+ANCHO_BOX
#define POS_Y2_BOX2_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX3_PI       POS_X2_BOX2_PI+GAP_BOX   
#define POS_Y1_BOX3_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX3_PI       POS_X1_BOX3_PI+ANCHO_BOX
#define POS_Y2_BOX3_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX4_PI       POS_X2_BOX3_PI+GAP_BOX   
#define POS_Y1_BOX4_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX4_PI       POS_X1_BOX4_PI+ANCHO_BOX
#define POS_Y2_BOX4_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX5_PI       POS_X2_BOX4_PI+GAP_BOX   
#define POS_Y1_BOX5_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX5_PI       POS_X1_BOX5_PI+ANCHO_BOX
#define POS_Y2_BOX5_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX6_PI       POS_X2_BOX5_PI+GAP_BOX   
#define POS_Y1_BOX6_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX6_PI       POS_X1_BOX6_PI+ANCHO_BOX
#define POS_Y2_BOX6_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX7_PI       POS_X2_BOX6_PI+GAP_BOX   
#define POS_Y1_BOX7_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX7_PI       POS_X1_BOX7_PI+ANCHO_BOX
#define POS_Y2_BOX7_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX8_PI       POS_X2_BOX7_PI+GAP_BOX   
#define POS_Y1_BOX8_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX8_PI       POS_X1_BOX8_PI+ANCHO_BOX
#define POS_Y2_BOX8_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX9_PI       POS_X2_BOX8_PI+GAP_BOX   
#define POS_Y1_BOX9_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX9_PI       POS_X1_BOX9_PI+ANCHO_BOX
#define POS_Y2_BOX9_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX10_PI       POS_X2_BOX9_PI+GAP_BOX   
#define POS_Y1_BOX10_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX10_PI       POS_X1_BOX10_PI+ANCHO_BOX
#define POS_Y2_BOX10_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX11_PI       POS_X2_BOX10_PI+GAP_BOX   
#define POS_Y1_BOX11_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX11_PI       POS_X1_BOX11_PI+ANCHO_BOX
#define POS_Y2_BOX11_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX12_PI       POS_X2_BOX11_PI+GAP_BOX   
#define POS_Y1_BOX12_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX12_PI       POS_X1_BOX12_PI+ANCHO_BOX
#define POS_Y2_BOX12_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX13_PI       POS_X2_BOX12_PI+GAP_BOX   
#define POS_Y1_BOX13_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX13_PI       POS_X1_BOX13_PI+ANCHO_BOX
#define POS_Y2_BOX13_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX14_PI       POS_X2_BOX13_PI+GAP_BOX   
#define POS_Y1_BOX14_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX14_PI       POS_X1_BOX14_PI+ANCHO_BOX
#define POS_Y2_BOX14_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX15_PI       POS_X2_BOX14_PI+GAP_BOX   
#define POS_Y1_BOX15_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX15_PI       POS_X1_BOX15_PI+ANCHO_BOX
#define POS_Y2_BOX15_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX16_PI       POS_X2_BOX15_PI+GAP_BOX   
#define POS_Y1_BOX16_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX16_PI       POS_X1_BOX16_PI+ANCHO_BOX
#define POS_Y2_BOX16_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX17_PI       POS_X2_BOX16_PI+GAP_BOX   
#define POS_Y1_BOX17_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX17_PI       POS_X1_BOX17_PI+ANCHO_BOX
#define POS_Y2_BOX17_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX18_PI       POS_X2_BOX17_PI+GAP_BOX   
#define POS_Y1_BOX18_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX18_PI       POS_X1_BOX18_PI+ANCHO_BOX
#define POS_Y2_BOX18_PI       POS_Y2_BOX_PI-GAP_BOX

#define POS_X1_BOX19_PI       POS_X2_BOX18_PI+GAP_BOX   
#define POS_Y1_BOX19_PI       POS_Y1_BOX_PI+GAP_BOX
#define POS_X2_BOX19_PI       POS_X1_BOX19_PI+ANCHO_BOX
#define POS_Y2_BOX19_PI       POS_Y2_BOX_PI-GAP_BOX



   //AJUSTE PARAMETRICO DE PRODUCTO
#define POS_X1_BOX_AP        14    //INICIO X1 portal INICIO
#define POS_Y1_BOX_AP        26//18    //INICIO Y1   PORTAL INICIO
#define POS_X2_BOX_AP        POS_X1_BOX_AP+LARGO_CUADRO_MADRE   //FIN X2 LARGO DE LA BOX PRINCIPAL X1-X2 PORTAL INICIO
#define POS_Y2_BOX_AP        POS_Y1_BOX_AP+ALTURA_CUADRO_MADRE    //FIN Y2 -> ALTURA BOX Y1-Y2   PORTAL INICIO

#define POS_X1_BOX1_AP       POS_X1_BOX_AP+GAP_BOX   
#define POS_Y1_BOX1_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX1_AP       POS_X1_BOX_AP+ANCHO_BOX
#define POS_Y2_BOX1_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX2_AP       POS_X2_BOX1_AP+GAP_BOX   
#define POS_Y1_BOX2_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX2_AP       POS_X1_BOX2_AP+ANCHO_BOX
#define POS_Y2_BOX2_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX3_AP       POS_X2_BOX2_AP+GAP_BOX   
#define POS_Y1_BOX3_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX3_AP       POS_X1_BOX3_AP+ANCHO_BOX
#define POS_Y2_BOX3_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX4_AP       POS_X2_BOX3_AP+GAP_BOX   
#define POS_Y1_BOX4_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX4_AP       POS_X1_BOX4_AP+ANCHO_BOX
#define POS_Y2_BOX4_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX5_AP       POS_X2_BOX4_AP+GAP_BOX   
#define POS_Y1_BOX5_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX5_AP       POS_X1_BOX5_AP+ANCHO_BOX
#define POS_Y2_BOX5_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX6_AP       POS_X2_BOX5_AP+GAP_BOX   
#define POS_Y1_BOX6_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX6_AP       POS_X1_BOX6_AP+ANCHO_BOX
#define POS_Y2_BOX6_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX7_AP       POS_X2_BOX6_AP+GAP_BOX   
#define POS_Y1_BOX7_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX7_AP       POS_X1_BOX7_AP+ANCHO_BOX
#define POS_Y2_BOX7_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX8_AP       POS_X2_BOX7_AP+GAP_BOX   
#define POS_Y1_BOX8_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX8_AP       POS_X1_BOX8_AP+ANCHO_BOX
#define POS_Y2_BOX8_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX9_AP       POS_X2_BOX8_AP+GAP_BOX   
#define POS_Y1_BOX9_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX9_AP       POS_X1_BOX9_AP+ANCHO_BOX
#define POS_Y2_BOX9_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX10_AP       POS_X2_BOX9_AP+GAP_BOX   
#define POS_Y1_BOX10_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX10_AP       POS_X1_BOX10_AP+ANCHO_BOX
#define POS_Y2_BOX10_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX11_AP       POS_X2_BOX10_AP+GAP_BOX   
#define POS_Y1_BOX11_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX11_AP       POS_X1_BOX11_AP+ANCHO_BOX
#define POS_Y2_BOX11_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX12_AP       POS_X2_BOX11_AP+GAP_BOX   
#define POS_Y1_BOX12_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX12_AP       POS_X1_BOX12_AP+ANCHO_BOX
#define POS_Y2_BOX12_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX13_AP       POS_X2_BOX12_AP+GAP_BOX   
#define POS_Y1_BOX13_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX13_AP       POS_X1_BOX13_AP+ANCHO_BOX
#define POS_Y2_BOX13_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX14_AP       POS_X2_BOX13_AP+GAP_BOX   
#define POS_Y1_BOX14_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX14_AP       POS_X1_BOX14_AP+ANCHO_BOX
#define POS_Y2_BOX14_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX15_AP       POS_X2_BOX14_AP+GAP_BOX   
#define POS_Y1_BOX15_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX15_AP       POS_X1_BOX15_AP+ANCHO_BOX
#define POS_Y2_BOX15_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX16_AP       POS_X2_BOX15_AP+GAP_BOX   
#define POS_Y1_BOX16_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX16_AP       POS_X1_BOX16_AP+ANCHO_BOX
#define POS_Y2_BOX16_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX17_AP       POS_X2_BOX16_AP+GAP_BOX   
#define POS_Y1_BOX17_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX17_AP       POS_X1_BOX17_AP+ANCHO_BOX
#define POS_Y2_BOX17_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX18_AP       POS_X2_BOX17_AP+GAP_BOX   
#define POS_Y1_BOX18_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX18_AP       POS_X1_BOX18_AP+ANCHO_BOX
#define POS_Y2_BOX18_AP       POS_Y2_BOX_AP-GAP_BOX

#define POS_X1_BOX19_AP       POS_X2_BOX18_AP+GAP_BOX   
#define POS_Y1_BOX19_AP       POS_Y1_BOX_AP+GAP_BOX
#define POS_X2_BOX19_AP       POS_X1_BOX19_AP+ANCHO_BOX
#define POS_Y2_BOX19_AP       POS_Y2_BOX_AP-GAP_BOX

   //PARAMETROS DE DETECCION-----------------------------------------
#define POS_X1_BOX_PD        0    //INICIO X1 portal INICIO
#define POS_Y1_BOX_PD        10    //INICIO Y1   PORTAL INICIO
#define POS_X2_BOX_PD        POS_X1_BOX_PD+LARGO_CUADRO_MADRE   //FIN X2 LARGO DE LA BOX PRINCIPAL X1-X2 PORTAL INICIO
#define POS_Y2_BOX_PD        POS_Y1_BOX_PD+ALTURA_CUADRO_MADRE    //FIN Y2 -> ALTURA BOX Y1-Y2   PORTAL INICIO

#define POS_X1_BOX1_PD       POS_X1_BOX_PD+GAP_BOX   
#define POS_Y1_BOX1_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX1_PD       POS_X1_BOX_PD+ANCHO_BOX
#define POS_Y2_BOX1_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX2_PD       POS_X2_BOX1_PD+GAP_BOX   
#define POS_Y1_BOX2_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX2_PD       POS_X1_BOX2_PD+ANCHO_BOX
#define POS_Y2_BOX2_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX3_PD       POS_X2_BOX2_PD+GAP_BOX   
#define POS_Y1_BOX3_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX3_PD       POS_X1_BOX3_PD+ANCHO_BOX
#define POS_Y2_BOX3_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX4_PD       POS_X2_BOX3_PD+GAP_BOX   
#define POS_Y1_BOX4_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX4_PD       POS_X1_BOX4_PD+ANCHO_BOX
#define POS_Y2_BOX4_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX5_PD       POS_X2_BOX4_PD+GAP_BOX   
#define POS_Y1_BOX5_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX5_PD       POS_X1_BOX5_PD+ANCHO_BOX
#define POS_Y2_BOX5_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX6_PD       POS_X2_BOX5_PD+GAP_BOX   
#define POS_Y1_BOX6_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX6_PD       POS_X1_BOX6_PD+ANCHO_BOX
#define POS_Y2_BOX6_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX7_PD       POS_X2_BOX6_PD+GAP_BOX   
#define POS_Y1_BOX7_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX7_PD       POS_X1_BOX7_PD+ANCHO_BOX
#define POS_Y2_BOX7_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX8_PD       POS_X2_BOX7_PD+GAP_BOX   
#define POS_Y1_BOX8_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX8_PD       POS_X1_BOX8_PD+ANCHO_BOX
#define POS_Y2_BOX8_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX9_PD       POS_X2_BOX8_PD+GAP_BOX   
#define POS_Y1_BOX9_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX9_PD       POS_X1_BOX9_PD+ANCHO_BOX
#define POS_Y2_BOX9_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX10_PD       POS_X2_BOX9_PD+GAP_BOX   
#define POS_Y1_BOX10_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX10_PD       POS_X1_BOX10_PD+ANCHO_BOX
#define POS_Y2_BOX10_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX11_PD       POS_X2_BOX10_PD+GAP_BOX   
#define POS_Y1_BOX11_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX11_PD       POS_X1_BOX11_PD+ANCHO_BOX
#define POS_Y2_BOX11_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX12_PD       POS_X2_BOX11_PD+GAP_BOX   
#define POS_Y1_BOX12_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX12_PD       POS_X1_BOX12_PD+ANCHO_BOX
#define POS_Y2_BOX12_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX13_PD       POS_X2_BOX12_PD+GAP_BOX   
#define POS_Y1_BOX13_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX13_PD       POS_X1_BOX13_PD+ANCHO_BOX
#define POS_Y2_BOX13_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX14_PD       POS_X2_BOX13_PD+GAP_BOX   
#define POS_Y1_BOX14_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX14_PD       POS_X1_BOX14_PD+ANCHO_BOX
#define POS_Y2_BOX14_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX15_PD       POS_X2_BOX14_PD+GAP_BOX   
#define POS_Y1_BOX15_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX15_PD       POS_X1_BOX15_PD+ANCHO_BOX
#define POS_Y2_BOX15_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX16_PD       POS_X2_BOX15_PD+GAP_BOX   
#define POS_Y1_BOX16_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX16_PD       POS_X1_BOX16_PD+ANCHO_BOX
#define POS_Y2_BOX16_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX17_PD       POS_X2_BOX16_PD+GAP_BOX   
#define POS_Y1_BOX17_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX17_PD       POS_X1_BOX17_PD+ANCHO_BOX
#define POS_Y2_BOX17_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX18_PD       POS_X2_BOX17_PD+GAP_BOX   
#define POS_Y1_BOX18_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX18_PD       POS_X1_BOX18_PD+ANCHO_BOX
#define POS_Y2_BOX18_PD       POS_Y2_BOX_PD-GAP_BOX

#define POS_X1_BOX19_PD       POS_X2_BOX18_PD+GAP_BOX   
#define POS_Y1_BOX19_PD       POS_Y1_BOX_PD+GAP_BOX
#define POS_X2_BOX19_PD       POS_X1_BOX19_PD+ANCHO_BOX
#define POS_Y2_BOX19_PD       POS_Y2_BOX_PD-GAP_BOX
//  FIN de contantes de Ajustes Avanzados



//void displayCuadroMadre(void);
unsigned char displayCuadroMadre_VFD(void);
#endif /* BARRADISPLAY_H_ ************************************************************/