Solution
========

==============
Solution order
==============

#. Solve water surface equation for :math:`\eta` at time level n+1
#. Compute U at n+1 using the momentum equation
#. Compute W at n+1 using the continuity equation

=========================
Solution for :math:`\eta`
=========================

.. math:: A\eta^n_{i-1} + X\eta^n_i + C\eta^n_{i+1} = D

where

.. math::

  A = & \left[ \frac{-g\Delta t^2}{\Delta x} \sum^{kb}_{kt}BH_r \bigg\vert_{i-1} \right] \\
  X = & \left[B_\eta\Delta x + \frac{g\Delta t^2}{\Delta x}\left\{ \sum^{kb}_{kt}BH_r \bigg\vert_i + \sum^{kb}_{kt}BH_r \bigg\vert_{i-1}\right\} \right] \\
  C = & \left[\frac{-g\Delta t^2}{\Delta x}\sum^{kb}_{kt}BH_r \bigg\vert_i\right] \\
  D = & \Delta t\sum^{kb}_{kt}\left(UBH_r\vert_i - UBH_r\vert_{i-1}\right) + B_\eta\eta^{n-1}_i\Delta x
    + \Delta t^2\sum^{kb}_{kt}\left(FH_r\vert_i - FH_r\vert_{i-1}\right) \\
    & + \Delta t^2\frac{g}{\rho}\sum^{kb}_{kt}\left(BH_r\vert_i
    - BH_r\vert_{i-1}\right)\sum_{kt}^{kb}\frac{\partial\rho}{\partial x}H_r \\
    & + \frac{\Delta t^2}{\rho}\left[\left(B\tau_{xz}\vert_h - B\tau_{xz}\vert_\eta\right)_i
    - \left(B\tau_{xz}\vert_h - B\tau_{xz}\vert_\eta\right)_{i-1}\right]
