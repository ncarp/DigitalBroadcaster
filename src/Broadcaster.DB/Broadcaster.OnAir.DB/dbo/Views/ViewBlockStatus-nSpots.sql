
CREATE VIEW [dbo].[ViewBlockStatus-nSpots]
AS
SELECT dbo.ViewTrafficDetails.BlockID, 
    dbo.ViewTrafficDetails.BlockDate, 
    COUNT(dbo.BlocksDefinition.ID) AS nSpots, 
    SUM(dbo.ViewTrafficDetails.SpotLength) AS SpotsLength, 
    dbo.BlocksDefinition.Time, dbo.BlocksDefinition.Name
FROM dbo.BlocksDefinition INNER JOIN
    dbo.ViewTrafficDetails ON 
    dbo.BlocksDefinition.ID = dbo.ViewTrafficDetails.BlockID
GROUP BY dbo.ViewTrafficDetails.BlockID, 
    dbo.ViewTrafficDetails.BlockDate, dbo.BlocksDefinition.Time, 
    dbo.BlocksDefinition.Name

