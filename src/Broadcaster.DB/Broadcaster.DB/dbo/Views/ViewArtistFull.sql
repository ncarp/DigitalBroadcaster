CREATE VIEW [dbo].[ViewArtistFull]
AS
SELECT     dbo.Artists.ID, dbo.Artists.Name, dbo.Artists.Adress, dbo.Artists.www, dbo.Artists.Activ, dbo.Artists.NationalityID, dbo.Artists.Obs, dbo.Artists.eMail, 
                      dbo.Artists.Photo, dbo.Artists.DRM35, dbo.Artists.FanClub, dbo.Artists.Birthdate, dbo.Artists.RecordLabelID, dbo.Nationalities.Nationality AS Nationality,
                       dbo.RecordLabel.Name AS Label
FROM         dbo.Artists LEFT OUTER JOIN
                      dbo.RecordLabel ON dbo.Artists.RecordLabelID = dbo.RecordLabel.ID LEFT OUTER JOIN
                      dbo.Nationalities ON dbo.Artists.NationalityID = dbo.Nationalities.ID


