

CREATE VIEW [dbo].[ViewTrafficDetails]
AS
SELECT dbo.Traffic.ID, dbo.Traffic.BlockID, 
    dbo.BlocksDefinition.Name AS BlockName, 
    dbo.BlocksDefinition.Time AS BlockTime, 
    dbo.Traffic.BlockDate, dbo.Traffic.SpotID, 
    Broadcaster.dbo.Spots.Name AS SpotName, 
    Broadcaster.dbo.Spots.TypeOfBusinessID, 
    Broadcaster.dbo.Spots.Mix - Broadcaster.dbo.Spots.Start AS SpotLength,
     dbo.Traffic.Position, dbo.Traffic.ScheduleID, dbo.Traffic.Aired, 
    Broadcaster.dbo.TypeOfBusiness.Name AS Business, 
    Broadcaster.dbo.Customers.Name AS CustomerName
FROM dbo.BlocksDefinition INNER JOIN
    dbo.Traffic ON 
    dbo.BlocksDefinition.ID = dbo.Traffic.BlockID INNER JOIN
    Broadcaster.dbo.Spots ON 
    dbo.Traffic.SpotID = Broadcaster.dbo.Spots.ID INNER JOIN
    Broadcaster.dbo.Customers ON 
    Broadcaster.dbo.Spots.CustomerID = Broadcaster.dbo.Customers.ID LEFT
     OUTER JOIN
    Broadcaster.dbo.TypeOfBusiness ON 
    Broadcaster.dbo.Spots.TypeOfBusinessID = Broadcaster.dbo.TypeOfBusiness.ID

