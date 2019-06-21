
CREATE VIEW [dbo].[ViewSpotsSmallList]
AS
SELECT dbo.Spots.ID, RTRIM(dbo.Customers.Name) 
    + ' - ' + RTRIM(dbo.Spots.Name) AS Spot
FROM dbo.Spots INNER JOIN
    dbo.Customers ON dbo.Spots.CustomerID = dbo.Customers.ID



