
data = out.Relay;

ts = data(:,1);
yr = data(:,2);
ys = data(:,3);

figure
subplot(2,1,1)
plot(ts,yr)
grid on
subplot(2,1,2)
plot(ts,ys)
grid on

a = 0.43;
Tc = 14.1 - 12.7;
d = 1

Kc = (4 * d)/ (pi * a);

%% AH
Kp = 0.6 * Kc;
Ti = 0.5 * Tc;
Td = 0.25 * Ti;

%% KC

PM = 40;

Kp = Kc * cosd(PM);
Ti = Tc * ((1 + sind(PM))/(pi*cosd(PM)));
Td = 0.25 * Ti;

%% KJ

PM = 40;

td = ((PM - 37)/(360))* Tc

data = out.Relay_td;

tsa = data(:,1);
yra = data(:,2);
ysa = data(:,3);

figure
subplot(2,1,1)
plot(tsa,yra)
grid on
subplot(2,1,2)
plot(tsa,ysa)
grid on

a = 0.43;
Tc = 11.6 - 10.2;
d = 1

Kc = (4 * d)/ (pi * a);
Kp = 0.80 * Kc;
Ti = 0.64 * Tc;
Td = 0.25 * Ti;

