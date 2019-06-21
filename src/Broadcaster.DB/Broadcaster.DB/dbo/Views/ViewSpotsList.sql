
CREATE VIEW [dbo].[ViewSpotsList]
AS
SELECT dbo.Spots.ID, dbo.Spots.Name, dbo.Spots.CustomerID, 
    dbo.Spots.AgencyID, 
    dbo.Customers.Name AS CustomerName, 
    dbo.Agency.Name AS AgencyName, 
    dbo.Customers.SalespersonID, 
    dbo.Salesperson.Name AS SalespersonName
FROM dbo.Salesperson RIGHT OUTER JOIN
    dbo.Customers ON 
    dbo.Salesperson.ID = dbo.Customers.SalespersonID RIGHT OUTER
     JOIN
    dbo.Spots ON 
    dbo.Customers.ID = dbo.Spots.CustomerID LEFT OUTER JOIN
    dbo.Agency ON dbo.Spots.AgencyID = dbo.Agency.ID
WHERE (dbo.Spots.Activ = 1)



