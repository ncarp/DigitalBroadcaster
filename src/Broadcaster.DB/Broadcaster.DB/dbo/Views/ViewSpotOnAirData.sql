
CREATE VIEW [dbo].[ViewSpotOnAirData]
AS
SELECT dbo.Spots.CustomerID, dbo.Spots.ID AS SpotID, 
    dbo.HD.Path, dbo.Customers.Name AS CustomerName, 
    dbo.Spots.Name, dbo.Spots.FileName, dbo.Spots.Start, 
    dbo.Spots.Mix, dbo.Spots.Finish, 
    dbo.Spots.TypeOfBusinessID, dbo.Spots.MainVoiceID
FROM dbo.Spots INNER JOIN
    dbo.Customers ON 
    dbo.Spots.CustomerID = dbo.Customers.ID INNER JOIN
    dbo.HD ON dbo.Spots.PathID = dbo.HD.ID



