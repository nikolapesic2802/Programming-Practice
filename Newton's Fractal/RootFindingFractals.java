import java.util.Arrays;
import java.util.stream.IntStream;
import javafx.scene.image.PixelWriter;
import javafx.scene.image.WritableImage;
import javafx.scene.paint.Color;
import mars.drawingx.application.DrawingApplication;
import mars.drawingx.drawing.Drawing;
import mars.drawingx.drawing.DrawingUtils;
import mars.drawingx.drawing.View;
import mars.drawingx.gadgets.annotations.GadgetAnimation;
import mars.drawingx.gadgets.annotations.GadgetBoolean;
import mars.drawingx.gadgets.annotations.GadgetInteger;
import mars.drawingx.gadgets.annotations.GadgetVector;
import mars.geometry.Vector;

public class RootFindingFractals implements Drawing {
	public static int size = 800;
	@GadgetBoolean
	boolean coloringBasedOnIterations = true; // Color based on closest point or based on the number of iterations
	@GadgetInteger(min = 0, max = 6)
	int rootFindingMethod = 0; // 0-Newton, 1-Halley, 2-Schroeders, 3-B4, 4-EulerChebyshev, 5-Householder, 6-EzzatiSaleki

	@GadgetVector
	Vector CORNFLOWERBLUE = new Vector(0.66236 * factor, 0.56228 * factor);
	// @GadgetVector
	Vector DARKOLIVEGREEN = new Vector(0 * factor, 1 * factor);
	@GadgetVector
	Vector LIMEGREEN = new Vector(0 * factor, -1 * factor);
	//@GadgetVector
	Vector DEEPSKYBLUE = new Vector(-1.32472 * factor, 0 * factor);
	@GadgetVector
	Vector MEDIUMPURPLE = new Vector(0.66236 * factor, -0.56228 * factor);
	@GadgetInteger(min = 0, max = 100)
	int nIterations = 10;
	@GadgetInteger(min = 1, max = 10)
	int SuperSample = 1;
	public double aFactor = 200;
	public double cFactor = 10;
	@GadgetVector
	Vector aCoef = new Vector(aFactor - size / 2, 0);
	@GadgetVector
	Vector cCoef = new Vector(0, 0);
	@GadgetAnimation(min = -20, max = 100)
	double zoomToCenter = 0;
	@GadgetVector
	Vector centerPoint = new Vector(0, 0);

	public static int factor = 200;
	@GadgetInteger(min = 1, max = 100)
	public static int n = 5;

	public static class Complex {
		public double real;
		public double imaginary;

		public Complex(double real, double imaginary) {
			this.real = real;
			this.imaginary = imaginary;
		}

		public void add(Complex z) {
			this.real = this.real + z.real;
			this.imaginary = this.imaginary + z.imaginary;
		}

		public void sub(Complex z) {
			this.real = this.real - z.real;
			this.imaginary = this.imaginary - z.imaginary;
		}

		public void multiply(Complex z) {
			double _real = this.real * z.real - this.imaginary * z.imaginary;
			this.imaginary = this.real * z.imaginary + this.imaginary * z.real;
			this.real = _real;
		}

		public void multiply(double z) {
			this.real *= z;
			this.imaginary *= z;
		}

		public void divide(Complex z) {
			z.imaginary *= -1;
			this.multiply(z);
			this.divide(z.mod());
		}

		public void divide(double z) {
			this.real /= z;
			this.imaginary /= z;
		}

		public double mod() {
			return this.real * this.real + this.imaginary * this.imaginary;
		}

		public Complex sqrt() {
			double r = Math.sqrt(this.mod());
			double theta = Math.atan2(imaginary, real) / 2;
			return new Complex(r * Math.cos(theta), r * Math.sin(theta));
		}

		public Complex copy() {
			return new Complex(real, imaginary);
		}

		@Override
		public String toString() {
			return " " + real + " + " + imaginary + "i ";
		}
	}

	public Complex subtract(Complex z1, Complex z2) {
		return new Complex(z1.real - z2.real, z1.imaginary - z2.imaginary);
	}

	public Complex add(Complex z1, Complex z2) {
		return new Complex(z1.real + z2.real, z1.imaginary + z2.imaginary);
	}

	public Complex multiply(Complex z1, Complex z2) {
		Complex ans = new Complex(z1.real, z1.imaginary);
		ans.multiply(z2);
		return ans;
	}

	Vector[] lastVectors = null;

	Complex a, c;
	Complex[] p;
	static Color[] colors;
	static Complex[] bonusP;
	static Color[] bonusColor;

	static Complex[] coefPoly, coefDeri, coefDeri2, coefDeri3;

	public Complex[] getWithout(int j, int k, int l) {
		Complex[] ans = new Complex[n + 1];
		for (int i = 0; i <= n; i++)
			ans[i] = new Complex(i == 0 ? 1 : 0, 0);
		for (int x = 0; x < n; x++) {
			if (x != j && x != k && x != l) {
				for (int i = n; i > 0; i--) {
					ans[i] = add(ans[i - 1], multiply(ans[i], subtract(new Complex(0, 0), p[x])));
				}
				ans[0] = multiply(ans[0], subtract(new Complex(0, 0), p[x]));
			}
		}
		return ans;
	}

	public Complex[] getWithout(int j, int k) {
		return getWithout(j, k, n);
	}

	void calcCoefs() {
		coefPoly = getWithout(n, n);
		coefDeri = new Complex[n + 1];
		for (int i = 0; i <= n; i++)
			coefDeri[i] = new Complex(0, 0);
		for (int x = 0; x < n; x++) {
			Complex[] a = getWithout(x, n);
			for (int i = 0; i <= n; i++)
				coefDeri[i].add(a[i]);
		}
		coefDeri2 = new Complex[n + 1];
		for (int i = 0; i <= n; i++)
			coefDeri2[i] = new Complex(0, 0);

		for (int x = 0; x < n - 1; x++) {
			for (int y = x + 1; y < n; y++) {
				Complex[] a = getWithout(x, y);
				for (int i = 0; i <= n; i++)
					coefDeri2[i].add(a[i]);
				for (int i = 0; i <= n; i++)
					coefDeri2[i].add(a[i]);
			}
		}

		coefDeri3 = new Complex[n + 1];
		for (int i = 0; i <= n; i++)
			coefDeri3[i] = new Complex(0, 0);

		for (int x = 0; x < n - 2; x++) {
			for (int y = x + 1; y < n - 1; y++) {
				for (int z = y + 1; z < n; z++) {
					Complex[] a = getWithout(x, y, z);
					for (int i = 0; i <= n; i++) {
						a[i].multiply(6);
						coefDeri3[i].add(a[i]);
					}
				}
			}
		}
	}

	public Complex calcCoefs(Complex x, Complex[] coef) {
		Complex tr = new Complex(1, 0);
		Complex result = new Complex(1, 0);
		for (int i = 0; i <= n; i++) {
			result.add(multiply(tr, coef[i]));
			tr.multiply(x);
		}
		return result;
	}

	public void stepNewton(Complex z) { // https://en.wikipedia.org/wiki/Newton_fractal
		Complex p = calcCoefs(z, coefPoly);
		p.divide(calcCoefs(z, coefDeri));
		p.multiply(a);
		p.add(c);
		z.sub(p);
	}

	public void stepHalley(Complex z) { // https://en.wikipedia.org/wiki/Halley's_method
		Complex p = calcCoefs(z, coefPoly), d = calcCoefs(z, coefDeri), dd = calcCoefs(z, coefDeri2);
		dd.multiply(p);
		p.multiply(d);
		p.multiply(2);
		d.multiply(d);
		d.multiply(2);
		d.sub(dd);
		p.divide(d);
		p.multiply(a);
		p.add(c);
		z.sub(p);
	}

	public void stepSchroder(Complex z) { // https://mathworld.wolfram.com/SchroedersMethod.html
		Complex p = calcCoefs(z, coefPoly), d = calcCoefs(z, coefDeri), dd = calcCoefs(z, coefDeri2);
		dd.multiply(p);
		p.multiply(d);
		d.multiply(d);
		d.sub(dd);
		p.divide(d);
		p.multiply(a);
		p.add(c);
		z.sub(p);
	}

	public void stepB4(Complex z) {
		Complex p = calcCoefs(z, coefPoly), d = calcCoefs(z, coefDeri), dd = calcCoefs(z, coefDeri2),
				ddd = calcCoefs(z, coefDeri3);
		Complex g1 = d.copy();
		g1.multiply(d);
		g1.multiply(p);
		g1.multiply(6);
		Complex g2 = dd.copy();
		g2.multiply(p);
		g2.multiply(p);
		g2.multiply(3);
		g1.sub(g2);
		ddd.multiply(p);
		ddd.multiply(p);
		dd.multiply(d);
		dd.multiply(p);
		dd.multiply(6);
		ddd.sub(ddd);
		d.multiply(d);
		d.multiply(calcCoefs(z, coefDeri));
		d.multiply(6);
		ddd.add(d);
		g1.divide(ddd);
		g1.multiply(a);
		g1.add(c);
		z.sub(g1);
	}
	double m=0.2;
	public void stepEulerChebyshev(Complex z) {
		Complex p = calcCoefs(z, coefPoly), d = calcCoefs(z, coefDeri), dd = calcCoefs(z, coefDeri2);
		Complex prvi = p.copy();
		prvi.divide(d);
		Complex ostatak = prvi.copy();
		ostatak.multiply(prvi);
		ostatak.multiply(dd);
		ostatak.divide(d);
		ostatak.divide(2);
		ostatak.multiply(m);
		ostatak.multiply(m);
		prvi.multiply(m);
		prvi.multiply((3-m));
		prvi.divide(2);
		prvi.add(ostatak);
		prvi.multiply(a);
		prvi.add(c);
		z.sub(prvi);
	}
	
	public void stepHouseholder(Complex z) {
		Complex p = calcCoefs(z, coefPoly), d = calcCoefs(z, coefDeri), dd = calcCoefs(z, coefDeri2), ddd = calcCoefs(z, coefDeri3);
		Complex d1 = p.copy();
		d1.multiply(d);
		d1.multiply(d);
		d1.multiply(6);
		Complex d2 = p.copy();
		d2.multiply(p);
		d2.multiply(dd);
		d2.multiply(3);
		d1.sub(d2);
		ddd.multiply(p);
		ddd.multiply(p);
		dd.multiply(d);
		dd.multiply(p);
		dd.multiply(6);
		ddd.sub(dd);
		Complex x = d.copy();
		x.multiply(d);
		x.multiply(d);
		x.multiply(6);
		x.add(ddd);
		d1.divide(x);
		d1.multiply(a);
		d1.add(c);
		z.sub(d1);
	}
	
	public void stepEzzatiSaleki(Complex z) {
		Complex p = calcCoefs(z, coefPoly), d = calcCoefs(z, coefDeri);
		p.divide(d);
		Complex N = z.copy();
		stepNewton(N);
		Complex a1 = new Complex(1,0);
		a1.divide(d);
		Complex a4 = new Complex(4,0);
		d.add(calcCoefs(N, coefDeri));
		a4.divide(d);
		a1.sub(a4);
		a1.multiply(calcCoefs(N, coefPoly));
		p.sub(a1);
		p.multiply(a);
		p.add(c);
		z.sub(p);
	}

	public void step(Complex z) {
		if(rootFindingMethod == 6)
			stepEzzatiSaleki(z);
		else if(rootFindingMethod == 5)
			stepHouseholder(z);
		else if(rootFindingMethod == 4)
			stepEulerChebyshev(z);
		else if (rootFindingMethod == 3)
			stepB4(z);
		else if (rootFindingMethod == 2)
			stepSchroder(z);
		else if (rootFindingMethod == 1)
			stepHalley(z);
		else
			stepNewton(z);
	}

	public static WritableImage image;
	public static PixelWriter pw;

	double getVal(double iter) {
		double ratio = 0.85, start = 0.07;
		return 1 - start * (1 - Math.pow(ratio, iter)) / (1 - ratio);
	}

	public void draw(View view) {
		Vector[] nowVectors = { CORNFLOWERBLUE, DARKOLIVEGREEN, LIMEGREEN, DEEPSKYBLUE, MEDIUMPURPLE, aCoef, cCoef,
				new Vector(nIterations, SuperSample), new Vector(zoomToCenter, n), centerPoint,
				new Vector(rootFindingMethod, coloringBasedOnIterations ? 1 : 0) };
		double realzoomToCenter = Math.pow(1.5, zoomToCenter);
		if (!Arrays.equals(nowVectors, lastVectors)) {
			lastVectors = nowVectors;

			a = new Complex((aCoef.x + size / 2) / aFactor, aCoef.y / aFactor);
			c = new Complex(cCoef.x / cFactor * SuperSample, cCoef.y / cFactor * SuperSample);
			p = new Complex[Math.max(5, n)];
			p[0] = new Complex(CORNFLOWERBLUE.x * SuperSample, CORNFLOWERBLUE.y * SuperSample);
			p[4] = new Complex(DARKOLIVEGREEN.x * SuperSample, DARKOLIVEGREEN.y * SuperSample);
			p[1] = new Complex(LIMEGREEN.x * SuperSample, LIMEGREEN.y * SuperSample);
			p[3] = new Complex(DEEPSKYBLUE.x * SuperSample, DEEPSKYBLUE.y * SuperSample);
			p[2] = new Complex(MEDIUMPURPLE.x * SuperSample, MEDIUMPURPLE.y * SuperSample);
			for (int i = 5; i < n; i++) {
				p[i] = new Complex(bonusP[i - 5].real * SuperSample, bonusP[i - 5].imaginary * SuperSample);
			}

			colors = new Color[n];

			Color[] start = { Color.CORNFLOWERBLUE, Color.LIMEGREEN, Color.MEDIUMPURPLE, Color.DEEPSKYBLUE,
					Color.DARKOLIVEGREEN };
			for (int i = 0; i < Math.min(start.length, n); i++)
				colors[i] = start[i];
			for (int i = start.length; i < n; i++)
				colors[i] = bonusColor[i - start.length];

			calcCoefs();

			IntStream.range(0, size).parallel().forEach(i -> {
				for (int j = 0; j < size; j++) {
					int sumR = 0, sumG = 0, sumB = 0;
					for (int xk = 0; xk < SuperSample; xk++) {
						for (int yk = 0; yk < SuperSample; yk++) {
							Complex tr = new Complex(i * SuperSample + xk - size / 2 * SuperSample,
									-j * SuperSample - yk + size / 2 * SuperSample);
							tr.real /= realzoomToCenter;
							tr.imaginary /= realzoomToCenter;
							tr.real += centerPoint.x * SuperSample;
							tr.imaginary += centerPoint.y * SuperSample;

							Complex last = tr.copy();
							int cnt = 0;
							double plus = 0;
							double T = 10 * SuperSample * SuperSample;
							for (int k = 0; k < nIterations; k++) {
								for (int x = 0; coloringBasedOnIterations && x < n; x++) {
									if (subtract(tr, p[x]).mod() < T) {
										if (k == 0)
											plus = 0;
										else
											plus = (Math.log(T) - Math.log(subtract(tr, p[x]).mod()))
													/ (Math.log(subtract(last, p[x]).mod())
															- Math.log(subtract(tr, p[x]).mod()));
										k = nIterations;
										break;
									}
								}
								last = tr.copy();
								step(tr);
								cnt++;
							}
							double dist = Double.MAX_VALUE;
							int best = 0;
							for (int x = 0; x < n; x++) {
								double d = Math.min(dist, subtract(tr, p[x]).mod());
								if (d < dist) {
									dist = d;
									best = x;
								}
							}
							double mul = 255;
							if (coloringBasedOnIterations) {
								mul *= getVal(cnt - plus);
							}
							sumR += colors[best].getRed() * mul;
							sumG += colors[best].getGreen() * mul;
							sumB += colors[best].getBlue() * mul;
						}
					}
					sumR /= SuperSample * SuperSample;
					sumG /= SuperSample * SuperSample;
					sumB /= SuperSample * SuperSample;
					pw.setColor(i, j, Color.rgb(sumR, sumG, sumB));
				}
			});
		}
		DrawingUtils.clear(view, Color.gray(0.125));
		view.drawImageCentered(Vector.ZERO, image, 1);

		view.setFill(Color.RED);
		view.fillCircleCentered(new Vector(0, 0), 1);

		for (int i = 0; i < n; i++) {
			Vector where = new Vector((p[i].real - centerPoint.x * SuperSample) / SuperSample * realzoomToCenter,
					(p[i].imaginary - centerPoint.y * SuperSample) / SuperSample * realzoomToCenter);
			if (Math.abs(where.x) > size / 2 || Math.abs(where.y) > size / 2)
				continue;
			view.setFill(Color.gray(0.125));
			view.fillCircleCentered(where, 7);
			view.setFill(colors[i]);
			view.fillCircleCentered(where, 6.5);
		}
	}

	public static void main(String[] args) {
		bonusColor = new Color[100];
		for (int i = 0; i < 100; i++)
			bonusColor[i] = Color.rgb((int) (Math.random() * 255), (int) (Math.random() * 255),
					(int) (Math.random() * 255));
		bonusP = new Complex[100];
		for (int i = 0; i < 100; i++) {
			double x = Math.random() * size - size / 2;
			double y = Math.random() * size - size / 2;
			bonusP[i] = new Complex(x, y);
		}
		image = new WritableImage(size, size);
		pw = image.getPixelWriter();
		DrawingApplication.launch(800, 720);
	}

}
