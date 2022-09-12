

clc
close all
clear all

load PruebaA.mat

 tiempo = PruebaA(:,1);
entrada = PruebaA(:,2);
 salida = PruebaA(:,3);

figure(1)
subplot(2,1,1)
plot(tiempo,entrada)
grid minor 
axis([0 30 0 1.5])
subplot(2,1,2)
plot(tiempo,salida)
grid minor 
axis([0 30 0 1.5])

num = 1
den = [1 1 1]

sys = tf(num,den,'InputDelay',1)
t = 0:0.1:200;
u = (t < 1) * 0 + (t >= 1)*1; 

[ysim,tsim] = lsim(sys,u,t)

figure
plot(tiempo,salida,tsim,ysim)
grid minor 
axis([0 30 0 1.5])

