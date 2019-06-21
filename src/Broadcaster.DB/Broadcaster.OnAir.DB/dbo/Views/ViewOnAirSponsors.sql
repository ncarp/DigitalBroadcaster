
CREATE VIEW [dbo].[ViewOnAirSponsors]
AS
SELECT dbo.Sponsors.SpotID, dbo.Sponsors.StartingDate, 
    dbo.Sponsors.EndingDate, 
    Broadcaster.dbo.Spots.Name AS SpotName, 
    Broadcaster.dbo.Customers.Name AS CustomerName, 
    Broadcaster.dbo.Spots.Finish - Broadcaster.dbo.Spots.Start AS Length
FROM dbo.Sponsors INNER JOIN
    Broadcaster.dbo.Spots ON 
    dbo.Sponsors.SpotID = Broadcaster.dbo.Spots.ID INNER JOIN
    Broadcaster.dbo.Customers ON 
    Broadcaster.dbo.Spots.CustomerID = Broadcaster.dbo.Customers.ID

