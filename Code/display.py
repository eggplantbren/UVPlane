from pylab import *

posterior_sample = atleast_2d(loadtxt('posterior_sample.txt'))

figure(figsize=(8, 8))
ion()
hold(False)
for i in xrange(0, posterior_sample.shape[0]):
  N = int(posterior_sample[i, 3])
  x = posterior_sample[i, 4:104]
  y = posterior_sample[i, 104:204]
  f = posterior_sample[i, 204:304]

  x = x[0:N]
  y = y[0:N]
  f = f[0:N]

  scatter(x, y, s=f)
  axis([-10, 10, -10, 10])
  draw()

ioff()
show()

