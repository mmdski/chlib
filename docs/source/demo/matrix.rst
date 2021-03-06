Basic Matrix Operations
=======================
.. raw:: html

    <h2>Matrix multiplication</h2>

    <!-- The product of the identity matrix $I$ and a vector $x$ -->

    <p id="i-times-x-eq"></p>

    <!-- Testing an output block:

    <p id="output"></p> -->

    <!-- The product of $A$ and a vector $x$ -->

    <p id="a-times-x-eq"></p>

    <h2>Scalar multiplication</h2>

    <!-- The product of a scalar $c$ and the identity matrix $I$ -->

    <p id="c-times-i-eq"></p>

    <!-- The product of a scalar $c$ and $A$ -->

    <p id="c-times-a-eq"></p>

    <h2>Linear combination</h2>

    <!-- The linear combination of vectors $v$ and $w$ -->

    <p id="linear-combo-eq"></p>

    <h2>Transpose</h2>

    <!-- The transpose of $v$, $v^T$ -->

    <p id="v-transpose-eq"></p>

    <!-- The transpose of $A$, $A^T$ -->

    <p id="a-transpose-eq"></p>

    <h2>Dot product</h2>

    <!-- The dot product of vectors $v$ and $w$, $v^Tw$ -->

    <p id="v-w-dot-eq"></p>

    <script type="text/javascript">
        "use strict";

        var Module = {
            onRuntimeInitialized: function() {
                showDemo();
            }
        };

        function showDemo() {

            let n = 3;

            // define I
            let eye = Matrix.eye(n);

            // define x
            let x = Matrix.new(n, 1);
            for (let i = 1; i <= n; i++) {
                x.set(i, 1, getRandomInt());
            }

            // multiply I and x
            let xIProduct = eye.multiply(x);
            let xTimesIEq = document.getElementById("i-times-x-eq");
            xTimesIEq.textContent = "$$Ix = " + eye.toTex() + x.toTex() + "$$";
            xTimesIEq.textContent = "$$Ix = " + eye.toTex() + x.toTex() + " = " + xIProduct.toTex() + "$$";
            xIProduct.free();

            // matrix multiplication: Ax
            let a = Matrix.new(2, 3);
            for (let i = 1; i <= 2; i++) {
                for (let j = 1; j <= 3; j++) {
                    a.set(i, j, getRandomInt())
                }
            }
            let aXProduct = a.multiply(x);
            let aTimesXEq = document.getElementById("a-times-x-eq");
            aTimesXEq.textContent = "$$Ax = " + a.toTex() + x.toTex() + " = " + aXProduct.toTex() + "$$";
            x.free();
            aXProduct.free();

            // scalar multiplication by I
            let c = getRandomInt();
            while (c === 0)
                c = getRandomInt();
            let cIProduct = eye.multiply(c);
            let cTimesIEq = document.getElementById("c-times-i-eq");
            cTimesIEq.textContent = "$$cI = " + c + eye.toTex() + " = " + cIProduct.toTex() + "$$"
            cIProduct.free();
            eye.free();

            // // scalar multiplication by A
            let aIProduct = a.multiply(c);
            let aTimesIEq = document.getElementById("c-times-a-eq");
            aTimesIEq.textContent = "$$cA = " + c + a.toTex() + " = " + aIProduct.toTex() + "$$"
            aIProduct.free();

            // linear combination of v and w
            let v = Matrix.new(2, 1);
            let w = Matrix.new(2, 1);
            for (let i = 1; i <= 2; i++) {
                v.set(i, 1, getRandomInt());
                w.set(i, 1, getRandomInt());
            }
            let linearCombo = v.add(w);
            let linearComboEq = document.getElementById("linear-combo-eq");
            linearComboEq.textContent = "$$v + w = " + v.toTex() + " + " + w.toTex() + " = " + linearCombo.toTex() + "$$";
            linearCombo.free();

            // transpose v
            let vT = v.transpose();
            let vTEq = document.getElementById("v-transpose-eq");
            vTEq.textContent = "$$v^T = " + vT.toTex() + "$$";
            v.free();

            // transpose a
            let aT = a.transpose();
            let aTEq = document.getElementById("a-transpose-eq");
            aTEq.textContent = "$$A^T = " + aT.toTex() + "$$";
            a.free();
            aT.free();

            // dot product
            let vwDot = vT.multiply(w);
            let vwDotEq = document.getElementById("v-w-dot-eq");
            vwDotEq.textContent = "$$v^Tw = " + vT.toTex() + w.toTex() + " = " + vwDot + "$$";
            vT.free();
            w.free();

            MathJax.Hub.Queue(["Typeset", MathJax.Hub]);
        }

        function getMatrixTex(a) {

            let n_rows = _matrix_rows(a);
            let n_cols = _matrix_cols(a);

            let matrixTex = "\\begin{bmatrix}";
            for (let i = 1; i <= n_rows; i++) {
                matrixTex += " " + _matrix_get(a, i, 1);
                for (let j = 2; j <= n_cols; j++) {
                    matrixTex += " & " + _matrix_get(a, i, j);
                }
                if (i < n_rows)
                    matrixTex += " \\\\";
            }

            matrixTex += " \\end{bmatrix}";

            return matrixTex;
        }

        function getRandomInt() {
            let min = -10;
            let max = 10;
            return Math.floor(Math.random() * (max - min + 1) + min);
        }
    </script>
    <script type="text/javascript" src="../_static/js/chlib.js"></script>
    <script type="text/javascript" src="../_static/js/matrix.js"></script>
    <script type="text/x-mathjax-config">
    MathJax.Hub.Config({
        tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}
    });
    </script>
    <script src='//cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/MathJax.js?config=TeX-MML-AM_CHTML'></script>
