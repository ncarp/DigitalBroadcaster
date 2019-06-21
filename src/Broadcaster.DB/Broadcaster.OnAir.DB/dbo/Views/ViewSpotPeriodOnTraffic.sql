
CREATE VIEW [dbo].[ViewSpotPeriodOnTraffic]
AS
SELECT DISTINCT 
    dbo.Traffic.SpotID, MAX(dbo.Traffic.BlockDate) AS MaxDate, 
    MIN(dbo.Traffic.BlockDate) AS MinDate, 
    Broadcaster.dbo.Spots.Name AS SpotName
FROM dbo.Traffic INNER JOIN
    Broadcaster.dbo.Spots ON 
    dbo.Traffic.SpotID = Broadcaster.dbo.Spots.ID
GROUP BY dbo.Traffic.SpotID, Broadcaster.dbo.Spots.Name

