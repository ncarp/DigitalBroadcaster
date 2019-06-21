
CREATE VIEW [dbo].[ViewBumpedTraffic]
AS
SELECT Broadcaster.dbo.ViewSpotOnAirData.SpotID, 
    Broadcaster.dbo.ViewSpotOnAirData.CustomerName, 
    Broadcaster.dbo.ViewSpotOnAirData.Name, 
    Broadcaster.dbo.ViewSpotOnAirData.Finish - Broadcaster.dbo.ViewSpotOnAirData.Start
     AS Length, dbo.Traffic.BlockDate, dbo.Traffic.ID, 
    dbo.BlocksDefinition.Time
FROM dbo.Traffic INNER JOIN
    Broadcaster.dbo.ViewSpotOnAirData ON 
    dbo.Traffic.SpotID = Broadcaster.dbo.ViewSpotOnAirData.SpotID INNER
     JOIN
    dbo.BlocksDefinition ON 
    dbo.Traffic.BlockID = dbo.BlocksDefinition.ID
WHERE (dbo.Traffic.Aired = 0)

