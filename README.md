# Simulaci-n-Num-rica-y-Validaci-n-Anal-tica-de-Potencial-Electrost-tico-en-Geometr-as-Esf-ricas
Determinación de la distribución del potencial eléctrico en la región inter-esférica de dos conductores concéntricos. Aproximación analítica y modelado numérico basado en la resolución de la ecuación de Laplace

El sistema físico consiste en dos esferas conductoras concéntricas que definen un dominio de estudio radial. Se establecen condiciones de contorno de tipo Dirichlet en las superficies de ambos conductores:

- Esfera interior (R1​): Radio de 5 cm con un potencial fijo U1​=110 V.
- Esfera exterior (R2​): Radio de 10 cm con un potencial fijo U2​=0 V.

*Nota técnica:* El dominio de interés para la simulación y el cálculo analítico se restringe exclusivamente al espacio comprendido entre ambos radios, definido por el intervalo 5 cm≤r≤10 cm.

FUNDAMENTO MATEMÁTICO

*Solución Analítica*

La distribución teórica del potencial para esta configuración geométrica, derivada de las condiciones de simetría del sistema, se rige por la siguiente expresión general:

$$U(r)=U1​\cdot\frac{R1}{r}​​ \cdot\frac{(R2​−r)}{(R2​−R1​)}​$$

Tras realizar la sustitución de los parámetros específicos del modelo (R1​=5,R2​=10,U1​=110), se obtiene la función simplificada que describe el potencial en Voltios [V] en función del radio
r en centímetros [cm]:

$$U(r)=\frac{1100−110r}{r}​$$

*Solución Numérica (Ecuación de Laplace)*

El comportamiento del campo escalar de potencial en ausencia de carga neta entre los conductores se describe mediante la ecuación de Laplace. Debido a la simetría radial del problema, la ecuación en derivadas parciales (EDP) se reduce a una ecuación diferencial ordinaria (EDO) de segundo orden:

$$ \frac{d^2 U}{d^2 r} + (\frac{2}{r})\cdot \frac{dU}{dr}​=0 $$

Para resolver este problema de valores en el contorno (BVP), se ha implementado el método de disparo (shooting method). Esta técnica permite transformar el BVP en un problema de valores iniciales (IVP), facilitando la integración numérica mediante algoritmos iterativos y permitiendo que el sistema converja hacia el cumplimiento de las condiciones de Dirichlet impuestas en R2​.

IMPLEMENTACIÓN TÉCNICA

C++: Motor de cálculo numérico: Encargado de la discretización de la EDO, la implementación del método de disparo y la evaluación de la solución analítica. Genera los datasets en formato de texto plano (.txt) para asegurar la persistencia de los resultados.

MATLAB: Generación de figura con el dataset .txt

RESULTADOS Y COMPARATIVA

El análisis de los datos obtenidos permite caracterizar el perfil de decaimiento radial del potencial. Tal como se observa en los resultados representados en la gráfica 1 el potencial inicia en el valor prescrito de 110 V en la interfaz de la esfera interior (r=5 cm) y decrece de forma continua hasta anularse exactamente en el contorno exterior (r=10 cm).
<img width="711" height="578" alt="Captura de pantalla 2026-06-20 a las 19 00 57" src="https://github.com/user-attachments/assets/6fc09ac4-c59b-4d07-8b03-24c2bffff5a7" />

La comparativa entre la solución analítica y la solución numérica muestra una concordancia excepcional, con un error residual despreciable. Esta convergencia entre ambos métodos valida la implementación del motor de cálculo en C++ y confirma la robustez del método de disparo para abordar problemas de electrostática con simetría esférica.

CONCLUSIONES
- Validación Metodológica: Se confirma la efectividad y estabilidad del método de disparo para la resolución de ecuaciones diferenciales de tipo Laplace en geometrías unidimensionales.
- Rigor Numérico: La precisión del modelo numérico ha sido validada satisfactoriamente frente a la solución analítica, un paso crítico en el desarrollo de software científico antes de su escalado a geometrías complejas sin solución cerrada.
- Consistencia de Contorno: Los resultados demuestran el cumplimiento estricto de las condiciones de contorno de Dirichlet establecidas inicialmente (110 V y 0 V), garantizando la integridad física de la simulación.

