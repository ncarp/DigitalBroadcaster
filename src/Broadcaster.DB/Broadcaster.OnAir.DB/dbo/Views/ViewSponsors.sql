CREATE VIEW [dbo].[ViewSponsors]
AS
SELECT     dbo.Sponsors.SpotID, dbo.Sponsors.StartingDate, dbo.Sponsors.EndingDate, dbo.Sponsors.ID, Broadcaster.dbo.Spots.Name AS SpotName, 
                      Broadcaster.dbo.Customers.Name AS CustomerName, Broadcaster.dbo.Spots.CustomerID AS CustomerID
FROM         dbo.Sponsors INNER JOIN
                      Broadcaster.dbo.Spots ON dbo.Sponsors.SpotID = Broadcaster.dbo.Spots.ID INNER JOIN
                      Broadcaster.dbo.Customers ON Broadcaster.dbo.Spots.CustomerID = Broadcaster.dbo.Customers.ID
