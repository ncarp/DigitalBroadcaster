

CREATE VIEW [dbo].[ViewNBusiness]
AS
SELECT dbo.Traffic.BlockID, dbo.Traffic.BlockDate, 
    Broadcaster.dbo.Spots.TypeOfBusinessID, COUNT(*) AS N
FROM dbo.Traffic INNER JOIN
    Broadcaster.dbo.Spots ON 
    dbo.Traffic.SpotID = Broadcaster.dbo.Spots.ID
GROUP BY Broadcaster.dbo.Spots.TypeOfBusinessID, 
    dbo.Traffic.BlockDate, dbo.Traffic.BlockID

