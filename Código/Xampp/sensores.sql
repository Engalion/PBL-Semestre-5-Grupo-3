SELECT * FROM datacenter.sensores;

-- Por Minuto 

DROP VIEW sensores_pivot;

CREATE OR REPLACE VIEW sensores_pivot AS
SELECT
  DATE_FORMAT(data_hora, '%Y-%m-%d %H:%i') AS minuto,

  ROUND(MAX(CASE WHEN tipo = 'temperatura' THEN valor END), 1) AS temperatura,
  MAX(CASE WHEN tipo = 'humidade' THEN valor END) AS humidade,

  CASE
    WHEN MAX(CASE WHEN tipo = 'movimento' THEN valor END) = 1
      THEN 'Sim'
    ELSE 'Não'
  END AS movimento

FROM sensores
GROUP BY minuto
ORDER BY minuto DESC; 

SELECT *
FROM sensores_pivot
ORDER BY minuto DESC;


 -- Toda a Informação por segundo 

DROP VIEW sensores_pivot;

CREATE OR REPLACE VIEW sensores_pivot_segundo AS
SELECT
  DATE_FORMAT(data_hora, '%Y-%m-%d %H:%i:%s') AS instante,

  COALESCE(
    ROUND(MAX(CASE WHEN tipo = 'temperatura' THEN valor END), 1),
    ''
  ) AS temperatura,

  COALESCE(
    MAX(CASE WHEN tipo = 'humidade' THEN valor END),
    ''
  ) AS humidade,

  CASE
    WHEN MAX(CASE WHEN tipo = 'movimento' THEN valor END) = 1
      THEN 'Sim'
    ELSE 'Não'
  END AS movimento

FROM sensores
GROUP BY instante
ORDER BY instante DESC;


SELECT * FROM sensores_pivot_segundo;
