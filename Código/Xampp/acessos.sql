SELECT * FROM datacenter.acessos;

-- Por Minuto 
DROP VIEW sensores_pivot;

CREATE OR REPLACE VIEW acessos_pivot AS
SELECT
  DATE_FORMAT(data_hora, '%Y-%m-%d %H:%i') AS minuto,

  COALESCE(
    MAX(CASE WHEN estado = 'entrada' THEN id_usuario END),
    ''
  ) AS entrada_uid,

  COALESCE(
    MAX(CASE WHEN estado = 'saida' THEN id_usuario END),
    ''
  ) AS saida_uid,

  COALESCE(
    MAX(CASE WHEN estado = 'nao_autorizado' THEN id_usuario END),
    ''
  ) AS nao_autorizado_uid

FROM acessos
GROUP BY minuto
ORDER BY minuto DESC;

SELECT * FROM acessos_pivot;


-- Contagem por dia (entradas/saídas/não autorizado) 

SELECT
  DATE(data_hora) AS dia,
  SUM(estado='entrada') AS entradas,
  SUM(estado='saida') AS saidas,
  SUM(estado='nao_autorizado') AS nao_autorizados
FROM acessos
GROUP BY dia
ORDER BY dia DESC;
