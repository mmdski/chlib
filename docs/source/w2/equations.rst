Equations
=========

===================
Continuity Equation
===================

.. math::

  \frac{\partial UB}{\partial x} + \frac{\partial WB}{\partial z} = 0

===================
x-Momentum Equation
===================

.. math::

  \frac{\partial UB}{\partial t} + \frac{\partial UUB}{\partial x} + \frac{\partial WUB}{\partial z}
    = gB\frac{\partial \eta}{\partial x} - \frac{gB}{\rho}\int\limits^z_\eta\frac{\partial \rho}{\partial x}dz
    + \frac{1}{\rho}\frac{\partial B \tau_{xx}}{\partial x}
    + \frac{1}{\rho}\frac{\partial B \tau_{xz}}{\partial z}

===================
z-Momentum Equation
===================

.. math::

  0 = g - \frac{1}{\rho}\frac{\partial P}{\partial z}

============
Free Surface
============

.. math::

  B_\eta\frac{\partial \eta}{\partial t}
    = \frac{\partial}{\partial x}\int\limits^h_\eta UB dz

============
Shear Stress
============

Bottom Shear Stress
-------------------

.. math::

  \tau_b = \frac{\rho_w g}{C^2}U\lvert U \rvert

Vertical Shear Stress
---------------------

.. math::

  \frac{\tau_{xz}}{\rho} = \nu_t\frac{\partial U}{\partial z}

Total Vertical Shear Stress
---------------------------

.. math::

  \frac{\tau_{xz}}{\rho} = A_z\frac{\partial U}{\partial z} + \frac{\tau_b}{\rho}

Longitudinal Shear Stress
-------------------------

.. math::

  \frac{\tau_{xx}}{\rho} = A_x\frac{\partial U}{\partial x}

=======
Density
=======

.. math::

  \rho = \rho_T

.. math::

  \rho_{T_w} & = 999.842594 + 6.793952 \times 10^{-2}T_w \\
    & -9.095290 \times 10^{-3}T^2_w + 1.001685 \times 10^{-4}T^3_w \\
    & -1.120083 \times 10^{-6}T^4_w + 6.536332 \times 10^{-9}T^5_w

===================
Advection-diffusion
===================

.. math::

  \frac{\partial B \Phi}{\partial t} + \frac{\partial U B \Phi}{\partial x} + \frac{\partial WB\Phi}{\partial z}
    - \frac{\partial}{\partial x}\left[BD_x\frac{\partial\Phi}{\partial x}\right]
    - \frac{\partial}{\partial z}\left[BD_z\frac{\partial\Phi}{\partial z}\right]
    = S_{\Phi}B

.. math::

  D_x = 5.84 \times 10^{-4} \Delta x^{1.1}

.. math::

  D_z = 0.14A_z
