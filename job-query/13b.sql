SELECT MIN(cn.name) AS producing_company
FROM company_name AS cn, movie_companies AS mc
WHERE cn.country_code ='[us]'
AND cn.id = mc.company_id;
